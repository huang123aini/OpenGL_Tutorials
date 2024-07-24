
#pragma once

#include <vector>

#include "../Buffer.h"
#include "platform/GL.h"

namespace april {
namespace backend {

/**
 *存储顶点和索引数据
 */
class BufferGL : public Buffer {
 public:
  BufferGL(std::size_t size, BufferType type, BufferUsage usage);
  ~BufferGL();

  virtual void updateData(void* data, std::size_t size) override;

  virtual void updateSubData(void* data, std::size_t offset,
                             std::size_t size) override;

  virtual void usingDefaultStoredData(bool needDefaultStoredData) override;

  inline GLuint getHandler() const { return buffer_; }

 private:
  GLuint buffer_ = 0;
  std::size_t buffer_allocated_ = 0;
  char* data_ = nullptr;
  bool need_default_stored_data_ = true;
};
}  // namespace backend
}  // namespace april
