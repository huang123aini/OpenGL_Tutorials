/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 16:13:24
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 16:13:46
 * @FilePath:
 * /OpenGL_Tutorials/april/renderer/backend/opengl/DepthStencilStateGL.h
 */

#pragma once

#include "../DepthStencilState.h"

namespace april {
namespace backend {

/**
 * Set depth and stencil status to pipeline.
 */
class DepthStencilStateGL : public DepthStencilState {
 public:
  /// Reset to default state.
  static void reset();

  /**
   * @param descriptor Specifies the depth and stencil status.
   */
  DepthStencilStateGL(const DepthStencilDescriptor& descriptor);

  /**
   * Set depth and stencil status to pipeline.
   * @param stencilReferenceValueFront Specifies front stencil reference value.
   * @param stencilReferenceValueBack Specifies back stencil reference value.
   */
  void apply(unsigned int stencilReferenceValueFront,
             unsigned int stencilReferenceValueBack) const;
};
}  // namespace backend
}  // namespace april
