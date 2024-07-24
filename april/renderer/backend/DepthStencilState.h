/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 13:23:01
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 13:25:33
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/DepthStencilState.h
 */

#pragma once

#include "Macros.h"
#include "Types.h"
#include "base/Ref.h"

namespace april {
namespace backend {
/**
 * Stencil descriptor.
 */
struct StencilDescriptor {
  bool operator==(const StencilDescriptor& rhs) const;

  StencilOperation stencilFailureOperation = StencilOperation::KEEP;
  StencilOperation depthFailureOperation = StencilOperation::KEEP;
  StencilOperation depthStencilPassOperation = StencilOperation::KEEP;
  CompareFunction stencilCompareFunction = CompareFunction::ALWAYS;
  unsigned int readMask = 0;
  unsigned int writeMask = 0;
};

/**
 * Depth and stencil descriptor.
 */
struct DepthStencilDescriptor {
  CompareFunction depthCompareFunction = CompareFunction::LESS;
  bool depthWriteEnabled = false;
  bool depthTestEnabled = false;

  bool stencilTestEnabled = false;
  StencilDescriptor backFaceStencil;
  StencilDescriptor frontFaceStencil;
};

/**
 * Store Depth and stencil status.
 */
class DepthStencilState : public april::Ref {
 protected:
  /**
   * @param descriptor Specifies depth and stencil descriptor.
   */
  DepthStencilState(const DepthStencilDescriptor& descriptor);
  virtual ~DepthStencilState();

  DepthStencilDescriptor _depthStencilInfo;  ///< depth and stencil descriptor.
  bool _isBackFrontStencilEqual =
      false;  ///< Does front stencil status equals to back stencil's.
};

}  // namespace backend
}  // namespace april