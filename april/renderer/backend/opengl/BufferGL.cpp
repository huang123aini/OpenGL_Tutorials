/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 15:11:31
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 16:08:22
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/opengl/BufferGL.cpp
 */

#include "BufferGL.h"

#include <cassert>

#include "base/BaseMacros.h"

namespace april {
namespace backend {

namespace {
GLenum toGLUsage(const BufferUsage& usage) {
  switch (usage) {
    case BufferUsage::STATIC:
      return GL_STATIC_DRAW;
    case BufferUsage::DYNAMIC:
      return GL_DYNAMIC_DRAW;
    default:
      return GL_DYNAMIC_DRAW;
  }
}
}  // namespace

BufferGL::BufferGL(std::size_t size, BufferType type, BufferUsage usage)
    : Buffer(size, type, usage) {
  glGenBuffers(1, &buffer_);
}

BufferGL::~BufferGL() {
  if (buffer_) glDeleteBuffers(1, &buffer_);
}

void BufferGL::usingDefaultStoredData(bool needDefaultStoredData) {}

void BufferGL::updateData(void* data, std::size_t size) {
  assert(size && size <= size_);

  if (buffer_) {
    if (BufferType::VERTEX == type_) {
      glBindBuffer(GL_ARRAY_BUFFER, buffer_);
      glBufferData(GL_ARRAY_BUFFER, size, data, toGLUsage(usage_));
    } else {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, toGLUsage(usage_));
    }
    CHECK_GL_ERROR_DEBUG();
    buffer_allocated_ = size;
  }
}

void BufferGL::updateSubData(void* data, std::size_t offset, std::size_t size) {
  assert(buffer_allocated_ != 0);
  assert(offset + size <= buffer_allocated_);

  if (buffer_) {
    CHECK_GL_ERROR_DEBUG();
    if (BufferType::VERTEX == type_) {
      glBindBuffer(GL_ARRAY_BUFFER, buffer_);
      glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    } else {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_);
      glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
    }
    CHECK_GL_ERROR_DEBUG();
  }
}

}  // namespace backend
}  // namespace april
