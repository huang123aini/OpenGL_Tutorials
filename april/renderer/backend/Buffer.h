/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-22 16:30:40
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 15:52:49
 * @FilePath: /OpenGL_Tutorials/renderer/backend/Buffer.h
 */

#pragma once
#include <iostream>
#include <string>

#include "Types.h"
#include "base/Ref.h"

namespace april {
namespace backend {

class Buffer : public april::Ref {
 public:
  virtual void updateData(void* data, std::size_t size) = 0;

  virtual void updateSubData(void* data, std::size_t offset,
                             std::size_t size) = 0;

  virtual void usingDefaultStoredData(bool needDefaultStoredData) = 0;

  std::size_t getSize() const { return size_; }

 protected:
  Buffer(std::size_t size, BufferType type, BufferUsage usage)
      : usage_(usage), type_(type), size_(size) {}

  virtual ~Buffer() = default;

  BufferUsage usage_ = BufferUsage::DYNAMIC;  ///< Buffer usage.
  BufferType type_ = BufferType::VERTEX;      ///< Buffer type.
  std::size_t size_ = 0;                      ///< buffer size in bytes.
};

}  // namespace backend
}  // namespace april