/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 09:50:57
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 10:01:23
 * @FilePath: /OpenGL_Tutorials/renderer/backend/VertexLayout.cpp
 */

#include "VertexLayout.h"

#include <cassert>

namespace april {
namespace backend {

void VertexLayout::setAttribute(const std::string &name, std::size_t index,
                                VertexFormat format, std::size_t offset,
                                bool needToBeNormallized) {
  if (index == -1) return;
  attributes_[name] = {name, index, format, offset, needToBeNormallized};
}

void VertexLayout::setLayout(std::size_t stride) { stride_ = stride; }

}  // namespace backend
}  // namespace april
