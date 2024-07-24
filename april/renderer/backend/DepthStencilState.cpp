/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 13:23:11
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 13:24:46
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/DepthStencilState.cpp
 */

#include "DepthStencilState.h"

namespace april {
namespace backend {

bool StencilDescriptor::operator==(const StencilDescriptor& rhs) const {
  return (stencilFailureOperation == rhs.stencilFailureOperation &&
          depthFailureOperation == rhs.depthFailureOperation &&
          depthStencilPassOperation == rhs.depthStencilPassOperation &&
          stencilCompareFunction == rhs.stencilCompareFunction &&
          readMask == rhs.readMask && writeMask == rhs.writeMask);
}

DepthStencilState::DepthStencilState(const DepthStencilDescriptor& descriptor)
    : _depthStencilInfo(descriptor) {
  _isBackFrontStencilEqual =
      descriptor.backFaceStencil == descriptor.frontFaceStencil;
}

DepthStencilState::~DepthStencilState() {}

}  // namespace backend
}  // namespace april
