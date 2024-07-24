/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 11:16:05
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 11:17:32
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/RenderPassDescriptor.cpp
 */

#include "RenderPassDescriptor.h"

namespace april {
namespace backend {

RenderPassDescriptor& RenderPassDescriptor::operator=(
    const RenderPassDescriptor& descriptor) {
  clearDepthValue = descriptor.clearDepthValue;
  clearStencilValue = descriptor.clearStencilValue;
  clearColorValue = descriptor.clearColorValue;
  needColorAttachment = descriptor.needColorAttachment;
  depthTestEnabled = descriptor.depthTestEnabled;
  stencilTestEnabled = descriptor.stencilTestEnabled;
  needClearColor = descriptor.needClearColor;
  needClearDepth = descriptor.needClearDepth;
  needClearStencil = descriptor.needClearStencil;
  depthAttachmentTexture = descriptor.depthAttachmentTexture;
  stencilAttachmentTexture = descriptor.stencilAttachmentTexture;
  colorAttachmentsTexture[0] = descriptor.colorAttachmentsTexture[0];

  return *this;
}

bool RenderPassDescriptor::operator==(
    const RenderPassDescriptor& descriptor) const {
  if (clearDepthValue == descriptor.clearDepthValue &&
      clearStencilValue == descriptor.clearStencilValue &&
      clearColorValue == descriptor.clearColorValue &&
      needColorAttachment == descriptor.needColorAttachment &&
      depthTestEnabled == descriptor.depthTestEnabled &&
      stencilTestEnabled == descriptor.stencilTestEnabled &&
      needClearColor == descriptor.needClearColor &&
      needClearDepth == descriptor.needClearDepth &&
      needClearStencil == descriptor.needClearStencil &&
      depthAttachmentTexture == descriptor.depthAttachmentTexture &&
      stencilAttachmentTexture == descriptor.stencilAttachmentTexture &&
      colorAttachmentsTexture[0] == descriptor.colorAttachmentsTexture[0]) {
    return true;
  } else {
    return false;
  }
}

}  // namespace backend
}  // namespace april
