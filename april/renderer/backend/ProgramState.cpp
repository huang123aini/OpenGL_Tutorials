
#include "renderer/backend/ProgramState.h"

#include <algorithm>

// #include "base/CCDirector.h"
#include "renderer/backend/Program.h"
#include "renderer/backend/ProgramCache.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/Types.h"

#ifdef USE_METAL
#include "glsl_optimizer.h"
#endif

namespace april {
namespace backend {

namespace {
#define MAT3_SIZE 36
#define MAT4X3_SIZE 48
#define VEC3_SIZE 12
#define VEC4_SIZE 16
#define BVEC3_SIZE 3
#define BVEC4_SIZE 4
#define IVEC3_SIZE 12
#define IVEC4_SIZE 16

void convertbVec3TobVec4(const bool* src, bool* dst) {
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
  dst[3] = false;
}

void convertiVec3ToiVec4(const int* src, int* dst) {
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
  dst[3] = 0;
}

void convertVec3ToVec4(const float* src, float* dst) {
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
  dst[3] = 0.0f;
}

void convertMat3ToMat4x3(const float* src, float* dst) {
  dst[3] = dst[7] = dst[11] = 0.0f;
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
  dst[4] = src[3];
  dst[5] = src[4];
  dst[6] = src[5];
  dst[8] = src[6];
  dst[9] = src[7];
  dst[10] = src[8];
}
}  // namespace

// static field
std::vector<ProgramState::AutoBindingResolver*>
    ProgramState::_customAutoBindingResolvers;

TextureInfo::TextureInfo(const std::vector<uint32_t>& _slots,
                         const std::vector<backend::TextureBackend*> _textures)
    : slot(_slots), textures(_textures) {
  retainTextures();
}

TextureInfo::TextureInfo(const TextureInfo& other)
    : slot(other.slot),
      textures(other.textures)
#if CC_ENABLE_CACHE_TEXTURE_DATA
      ,
      location(other.location)
#endif
{
  retainTextures();
}

TextureInfo::~TextureInfo() { releaseTextures(); }

void TextureInfo::retainTextures() {
  for (auto& texture : textures) SAFE_RETAIN(texture);
}

void TextureInfo::releaseTextures() {
  for (auto& texture : textures) SAFE_RELEASE(texture);
}

TextureInfo& TextureInfo::operator=(TextureInfo&& rhs) {
  if (this != &rhs) {
    slot = rhs.slot;

    rhs.retainTextures();
    releaseTextures();
    textures = rhs.textures;

    // release the textures before cleaning the vertor
    rhs.releaseTextures();
    rhs.textures.clear();

#if CC_ENABLE_CACHE_TEXTURE_DATA
    location = rhs.location;
#endif
  }
  return *this;
}

TextureInfo& TextureInfo::operator=(const TextureInfo& rhs) {
  if (this != &rhs) {
    slot = rhs.slot;
    textures = rhs.textures;
    retainTextures();

#if CC_ENABLE_CACHE_TEXTURE_DATA
    location = rhs.location;
#endif
  }
  return *this;
}

ProgramState::ProgramState(Program* program) { init(program); }

bool ProgramState::init(Program* program) {
  SAFE_RETAIN(program);
  _program = program;
  _vertexUniformBufferSize =
      _program->getUniformBufferSize(ShaderStage::VERTEX);
  _vertexUniformBuffer = new char[_vertexUniformBufferSize];
  memset(_vertexUniformBuffer, 0, _vertexUniformBufferSize);

  return true;
}

void ProgramState::resetUniforms() {}

ProgramState::ProgramState() {}

ProgramState::~ProgramState() {
  SAFE_RELEASE(_program);
  SAFE_DELETE_ARRAY(_vertexUniformBuffer);
  SAFE_DELETE_ARRAY(_fragmentUniformBuffer);
}

ProgramState* ProgramState::clone() const {
  ProgramState* cp = new ProgramState();
  cp->_program = _program;
  cp->_vertexUniformBufferSize = _vertexUniformBufferSize;
  cp->_fragmentUniformBufferSize = _fragmentUniformBufferSize;
  cp->_vertexTextureInfos = _vertexTextureInfos;
  cp->_fragmentTextureInfos = _fragmentTextureInfos;
  cp->_vertexUniformBuffer = new char[_vertexUniformBufferSize];
  memcpy(cp->_vertexUniformBuffer, _vertexUniformBuffer,
         _vertexUniformBufferSize);
  cp->_vertexLayout = _vertexLayout;

  SAFE_RETAIN(cp->_program);

  return cp;
}

backend::UniformLocation ProgramState::getUniformLocation(
    backend::Uniform name) const {
  return _program->getUniformLocation(name);
}

backend::UniformLocation ProgramState::getUniformLocation(
    const std::string& uniform) const {
  return _program->getUniformLocation(uniform);
}

void ProgramState::setCallbackUniform(
    const backend::UniformLocation& uniformLocation,
    const UniformCallback& callback) {
  _callbackUniforms[uniformLocation] = callback;
}

void ProgramState::setUniform(const backend::UniformLocation& uniformLocation,
                              const void* data, std::size_t size) {
  switch (uniformLocation.shaderStage) {
    case backend::ShaderStage::VERTEX:
      setVertexUniform(uniformLocation.location[0], data, size,
                       uniformLocation.location[1]);
      break;
    case backend::ShaderStage::FRAGMENT:
      setFragmentUniform(uniformLocation.location[1], data, size);
      break;
    case backend::ShaderStage::VERTEX_AND_FRAGMENT:
      setVertexUniform(uniformLocation.location[0], data, size,
                       uniformLocation.location[1]);
      setFragmentUniform(uniformLocation.location[1], data, size);
      break;
    default:
      break;
  }
}

void ProgramState::setVertexUniform(int location, const void* data,
                                    std::size_t size, std::size_t offset) {
  if (location < 0) return;

  // float3 etc in Metal has both sizeof and alignment same as float4, need
  // convert to correct laytout
  memcpy(_vertexUniformBuffer + offset, data, size);
}

void ProgramState::setFragmentUniform(int location, const void* data,
                                      std::size_t size) {
  if (location < 0) return;
}

void ProgramState::setTexture(const backend::UniformLocation& uniformLocation,
                              uint32_t slot, backend::TextureBackend* texture) {
  switch (uniformLocation.shaderStage) {
    case backend::ShaderStage::VERTEX:
      setTexture(uniformLocation.location[0], slot, texture,
                 _vertexTextureInfos);
      break;
    case backend::ShaderStage::FRAGMENT:
      setTexture(uniformLocation.location[1], slot, texture,
                 _fragmentTextureInfos);
      break;
    case backend::ShaderStage::VERTEX_AND_FRAGMENT:
      setTexture(uniformLocation.location[0], slot, texture,
                 _vertexTextureInfos);
      setTexture(uniformLocation.location[1], slot, texture,
                 _fragmentTextureInfos);
      break;
    default:
      break;
  }
}

void ProgramState::setTextureArray(
    const backend::UniformLocation& uniformLocation,
    const std::vector<uint32_t>& slots,
    const std::vector<backend::TextureBackend*> textures) {
  switch (uniformLocation.shaderStage) {
    case backend::ShaderStage::VERTEX:
      setTextureArray(uniformLocation.location[0], slots, textures,
                      _vertexTextureInfos);
      break;
    case backend::ShaderStage::FRAGMENT:
      setTextureArray(uniformLocation.location[1], slots, textures,
                      _fragmentTextureInfos);
      break;
    case backend::ShaderStage::VERTEX_AND_FRAGMENT:
      setTextureArray(uniformLocation.location[0], slots, textures,
                      _vertexTextureInfos);
      setTextureArray(uniformLocation.location[1], slots, textures,
                      _fragmentTextureInfos);
      break;
    default:
      break;
  }
}

void ProgramState::setTexture(
    int location, uint32_t slot, backend::TextureBackend* texture,
    std::unordered_map<int, TextureInfo>& textureInfo) {
  if (location < 0) return;
  TextureInfo& info = textureInfo[location];
  info.releaseTextures();
  info.slot = {slot};
  info.textures = {texture};
  info.retainTextures();
}

void ProgramState::setTextureArray(
    int location, const std::vector<uint32_t>& slots,
    const std::vector<backend::TextureBackend*> textures,
    std::unordered_map<int, TextureInfo>& textureInfo) {
  assert(slots.size() == textures.size());
  TextureInfo& info = textureInfo[location];
  info.releaseTextures();
  info.slot = slots;
  info.textures = textures;
  info.retainTextures();
}

void ProgramState::setParameterAutoBinding(const std::string& uniform,
                                           const std::string& autoBinding) {
  _autoBindings.emplace(uniform, autoBinding);
  applyAutoBinding(uniform, autoBinding);
}

void ProgramState::applyAutoBinding(const std::string& uniformName,
                                    const std::string& autoBinding) {
  bool resolved = false;
  for (const auto resolver : _customAutoBindingResolvers) {
    resolved = resolver->resolveAutoBinding(this, uniformName, autoBinding);
    if (resolved) break;
  }
}

ProgramState::AutoBindingResolver::AutoBindingResolver() {
  _customAutoBindingResolvers.emplace_back(this);
}

ProgramState::AutoBindingResolver::~AutoBindingResolver() {
  auto& list = _customAutoBindingResolvers;
  list.erase(std::remove(list.begin(), list.end(), this), list.end());
}

void ProgramState::getVertexUniformBuffer(char** buffer,
                                          std::size_t& size) const {
  *buffer = _vertexUniformBuffer;
  size = _vertexUniformBufferSize;
}

void ProgramState::getFragmentUniformBuffer(char** buffer,
                                            std::size_t& size) const {
  *buffer = _fragmentUniformBuffer;
  size = _fragmentUniformBufferSize;
}

}  // namespace backend
}  // namespace april
