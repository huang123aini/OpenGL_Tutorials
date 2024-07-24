/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 09:42:22
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 09:47:19
 * @FilePath: /OpenGL_Tutorials/renderer/backend/Types.cpp
 */

#include "Types.h"

namespace april {
namespace backend {

bool UniformLocation::operator==(const UniformLocation &other) const {
  return (shaderStage == other.shaderStage &&
          location[0] == other.location[0] && location[1] == other.location[1]);
}

std::size_t UniformLocation::operator()(const UniformLocation &uniform) const {
  return (((size_t)shaderStage) & 0xF) | ((size_t)(location[0] << 4)) |
         ((size_t)(location[1] << 8));
}

}  // namespace backend
}  // namespace april
