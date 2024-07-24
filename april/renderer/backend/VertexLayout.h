/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 09:50:39
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 14:27:48
 * @FilePath: /OpenGL_Tutorials/renderer/backend/VertexLayout.h
 */

#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "Types.h"
#include "base/Ref.h"

namespace april {
namespace backend {

/**
 * 存储顶点属性布局
 */
class VertexLayout {
 public:
  struct Attribute {
    Attribute() = default;
    Attribute(const std::string& name, std::size_t index, VertexFormat format,
              std::size_t offset, bool needToBeNormallized)
        : name_(name),
          format_(format),
          offset_(offset),
          index_(index),
          need_to_be_normallized_(needToBeNormallized) {}

    std::string name_;
    VertexFormat format_ = VertexFormat::INT3;
    std::size_t offset_ = 0;
    std::size_t index_ = 0;
    bool need_to_be_normallized_ = false;
  };

  VertexLayout() = default;

  void setAttribute(const std::string& name, std::size_t index,
                    VertexFormat format, std::size_t offset,
                    bool needToBeNormallized);

  /**
   * Set stride of vertices. the distance between the data of two vertices, in
   * bytes.
   */
  void setLayout(std::size_t stride);

  inline std::size_t getStride() const { return stride_; }

  inline const std::unordered_map<std::string, Attribute>& getAttributes()
      const {
    return attributes_;
  }

  /**
   * Check if vertex layout has been set.
   */
  inline bool isValid() const { return stride_ != 0; }

 private:
  std::unordered_map<std::string, Attribute> attributes_;
  std::size_t stride_ = 0;
};

}  // namespace backend
}  // namespace april