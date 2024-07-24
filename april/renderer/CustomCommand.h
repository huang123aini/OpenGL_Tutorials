
#pragma once

#include "renderer/RenderCommand.h"

namespace april {

namespace backend {
class Buffer;
}

/**
Custom command is used to draw all things except triangle commands. You can use
this command to draw things, just provide vertex/index data and set corret
flags.
*/
class CustomCommand : public RenderCommand {
 public:
  enum class DrawType { ARRAY, ELEMENT };

  using PrimitiveType = backend::PrimitiveType;

  using BufferUsage = backend::BufferUsage;

  using IndexFormat = backend::IndexFormat;

  typedef std::function<void()> CallBackFunc;

  CustomCommand();
  ~CustomCommand();

 public:
  void init(float globalZOrder, const glm::mat4& modelViewTransform,
            unsigned int flags);

  void init(float globalZOrder);

  void init(float globalZOrder, const BlendFunc& blendFunc);

  void createVertexBuffer(std::size_t vertexSize, std::size_t capacity,
                          BufferUsage usage);

  void createIndexBuffer(IndexFormat format, std::size_t capacity,
                         BufferUsage usage);

  void updateVertexBuffer(void* data, std::size_t length);

  void updateIndexBuffer(void* data, std::size_t length);

  void updateVertexBuffer(void* data, std::size_t offset, std::size_t length);

  void updateIndexBuffer(void* data, std::size_t offset, std::size_t length);

  inline std::size_t getVertexCapacity() const { return _vertexCapacity; }

  inline std::size_t getIndexCapacity() const { return _indexCapacity; }

  inline void setDrawType(DrawType drawType) { _drawType = drawType; }
  inline DrawType getDrawType() const { return _drawType; }

  inline void setPrimitiveType(PrimitiveType primitiveType) {
    _primitiveType = primitiveType;
  }
  inline PrimitiveType getPrimitiveType() const { return _primitiveType; }

  void setVertexBuffer(backend::Buffer* vertexBuffer);
  inline backend::Buffer* getVertexBuffer() const { return _vertexBuffer; }

  void setIndexBuffer(backend::Buffer* indexBuffer, IndexFormat indexFormat);
  inline backend::Buffer* getIndexBuffer() const { return _indexBuffer; }

  inline void setVertexDrawInfo(std::size_t start, std::size_t count) {
    _vertexDrawStart = start;
    _vertexDrawCount = count;
  }
  inline std::size_t getVertexDrawStart() const { return _vertexDrawStart; }
  inline std::size_t getVertexDrawCount() const { return _vertexDrawCount; }

  inline void setIndexDrawInfo(std::size_t start, std::size_t count) {
    _indexDrawOffset = start * _indexSize;
    _indexDrawCount = count;
  }
  inline std::size_t getIndexDrawOffset() const { return _indexDrawOffset; }
  inline std::size_t getIndexDrawCount() const { return _indexDrawCount; }

  inline void setLineWidth(float lineWidth) { _lineWidth = lineWidth; }
  inline float getLineWidth() const { return _lineWidth; }

  inline IndexFormat getIndexFormat() const { return _indexFormat; }

  std::function<void()> func;

  void setBeforeCallback(const CallBackFunc& before) {
    _beforeCallback = before;
  }

  /**
   * set a callback which will be invoke after rendering
   */
  void setAfterCallback(const CallBackFunc& after) { _afterCallback = after; }

  const CallBackFunc& getBeforeCallback() { return _beforeCallback; }

  const CallBackFunc& getAfterCallback() { return _afterCallback; }

 protected:
  std::size_t computeIndexSize() const;

  backend::Buffer* _vertexBuffer = nullptr;
  backend::Buffer* _indexBuffer = nullptr;

  std::size_t _vertexDrawStart = 0;
  std::size_t _vertexDrawCount = 0;

  std::size_t _indexDrawOffset = 0;
  std::size_t _indexDrawCount = 0;

  DrawType _drawType = DrawType::ELEMENT;
  PrimitiveType _primitiveType = PrimitiveType::TRIANGLE;
  IndexFormat _indexFormat = IndexFormat::U_SHORT;

  float _lineWidth = 0.0;

  std::size_t _indexSize = 0;

  std::size_t _vertexCapacity = 0;
  std::size_t _indexCapacity = 0;

  CallBackFunc _beforeCallback = nullptr;
  CallBackFunc _afterCallback = nullptr;
};

}  // namespace april