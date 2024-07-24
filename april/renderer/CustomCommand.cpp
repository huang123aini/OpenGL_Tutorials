
#include "renderer/CustomCommand.h"

// #include "base/ccUtils.h"
// #include "renderer/CCTextureAtlas.h"
#include "renderer/backend/Buffer.h"
#include "renderer/backend/Device.h"

namespace april {

CustomCommand::CustomCommand() { _type = RenderCommand::Type::CUSTOM_COMMAND; }

CustomCommand::~CustomCommand() {
  SAFE_RELEASE(_vertexBuffer);
  SAFE_RELEASE(_indexBuffer);
}

void CustomCommand::init(float depth, const glm::mat4& modelViewTransform,
                         unsigned int flags) {
  RenderCommand::init(depth, modelViewTransform, flags);
}

void CustomCommand::init(float globalZOrder) { _globalOrder = globalZOrder; }

void CustomCommand::init(float globalZOrder, const BlendFunc& blendFunc) {
  _globalOrder = globalZOrder;

  auto& blendDescriptor = _pipelineDescriptor.blendDescriptor;
  blendDescriptor.blendEnabled = true;
  blendDescriptor.sourceRGBBlendFactor =
      blendDescriptor.sourceAlphaBlendFactor = blendFunc.src;
  blendDescriptor.destinationRGBBlendFactor =
      blendDescriptor.destinationAlphaBlendFactor = blendFunc.dst;
}

void CustomCommand::createVertexBuffer(std::size_t vertexSize,
                                       std::size_t capacity,
                                       BufferUsage usage) {
  SAFE_RELEASE(_vertexBuffer);

  _vertexCapacity = capacity;
  _vertexDrawCount = capacity;

  auto device = backend::Device::getInstance();
  _vertexBuffer = device->newBuffer(vertexSize * capacity,
                                    backend::BufferType::VERTEX, usage);
}

void CustomCommand::createIndexBuffer(IndexFormat format, std::size_t capacity,
                                      BufferUsage usage) {
  SAFE_RELEASE(_indexBuffer);

  _indexFormat = format;
  _indexSize = computeIndexSize();
  _indexCapacity = capacity;
  _indexDrawCount = capacity;

  auto device = backend::Device::getInstance();
  _indexBuffer = device->newBuffer(_indexSize * capacity,
                                   backend::BufferType::INDEX, usage);
}

void CustomCommand::updateVertexBuffer(void* data, std::size_t offset,
                                       std::size_t length) {
  assert(_vertexBuffer);
  _vertexBuffer->updateSubData(data, offset, length);
}

void CustomCommand::updateIndexBuffer(void* data, std::size_t offset,
                                      std::size_t length) {
  assert(_indexBuffer);
  _indexBuffer->updateSubData(data, offset, length);
}

void CustomCommand::setVertexBuffer(backend::Buffer* vertexBuffer) {
  if (_vertexBuffer == vertexBuffer) return;

  SAFE_RELEASE(_vertexBuffer);
  _vertexBuffer = vertexBuffer;
  SAFE_RETAIN(_vertexBuffer);
}

void CustomCommand::setIndexBuffer(backend::Buffer* indexBuffer,
                                   IndexFormat format) {
  if (_indexBuffer == indexBuffer && _indexFormat == format) return;

  SAFE_RELEASE(_indexBuffer);
  _indexBuffer = indexBuffer;
  SAFE_RETAIN(_indexBuffer);

  _indexFormat = format;
  _indexSize = computeIndexSize();
}

void CustomCommand::updateVertexBuffer(void* data, std::size_t length) {
  assert(_vertexBuffer);
  _vertexBuffer->updateData(data, length);
}

void CustomCommand::updateIndexBuffer(void* data, std::size_t length) {
  assert(_indexBuffer);
  _indexBuffer->updateData(data, length);
}

std::size_t CustomCommand::computeIndexSize() const {
  if (IndexFormat::U_SHORT == _indexFormat)
    return sizeof(unsigned short);
  else
    return sizeof(unsigned int);
}

}  // namespace april
