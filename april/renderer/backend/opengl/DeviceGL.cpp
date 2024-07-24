
#include "DeviceGL.h"

#include "BufferGL.h"
#include "CommandBufferGL.h"
#include "DepthStencilStateGL.h"
#include "DeviceInfoGL.h"
#include "ProgramGL.h"
#include "RenderPipelineGL.h"
#include "ShaderModuleGL.h"
#include "TextureGL.h"

namespace april {
namespace backend {

Device* Device::getInstance() {
  if (!_instance) _instance = new (std::nothrow) DeviceGL();

  return _instance;
}

DeviceGL::DeviceGL() {
  _deviceInfo = new (std::nothrow) DeviceInfoGL();
  if (!_deviceInfo || _deviceInfo->init() == false) {
    delete _deviceInfo;
    _deviceInfo = nullptr;
  }
}

DeviceGL::~DeviceGL() {
  ProgramCache::destroyInstance();
  delete _deviceInfo;
  _deviceInfo = nullptr;
}

CommandBuffer* DeviceGL::newCommandBuffer() {
  return new (std::nothrow) CommandBufferGL();
}

Buffer* DeviceGL::newBuffer(std::size_t size, BufferType type,
                            BufferUsage usage) {
  return new (std::nothrow) BufferGL(size, type, usage);
}

TextureBackend* DeviceGL::newTexture(const TextureDescriptor& descriptor) {
  switch (descriptor.textureType) {
    case TextureType::TEXTURE_2D:
      return new (std::nothrow) Texture2DGL(descriptor);
    case TextureType::TEXTURE_CUBE:
      return new (std::nothrow) TextureCubeGL(descriptor);
    default:
      return nullptr;
  }
}

ShaderModule* DeviceGL::newShaderModule(ShaderStage stage,
                                        const std::string& source) {
  return new (std::nothrow) ShaderModuleGL(stage, source);
}

DepthStencilState* DeviceGL::createDepthStencilState(
    const DepthStencilDescriptor& descriptor) {
  auto ret = new (std::nothrow) DepthStencilStateGL(descriptor);
  if (ret) ret->autorelease();

  return ret;
}

RenderPipeline* DeviceGL::newRenderPipeline() {
  return new (std::nothrow) RenderPipelineGL();
}

Program* DeviceGL::newProgram(const std::string& vertexShader,
                              const std::string& fragmentShader) {
  return new (std::nothrow) ProgramGL(vertexShader, fragmentShader);
}

}  // namespace backend
}  // namespace april
