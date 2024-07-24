/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 11:15:48
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 13:20:09
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/RenderPassDescriptor.h
 */

#pragma once

#include <array>
#include <vector>

#include "Macros.h"
#include "Types.h"

namespace april {
namespace backend {

class TextureBackend;
/**
 * @addtogroup _backend
 * @{
 */

/**
 * Store values about color, depth and stencil attachment.
 *
 * 存储颜色 深度 模板
 */
struct RenderPassDescriptor {
  RenderPassDescriptor& operator=(const RenderPassDescriptor& descriptor);
  bool operator==(const RenderPassDescriptor& descriptor) const;
  bool needDepthStencilAttachment() const {
    return depthTestEnabled || stencilTestEnabled;
  }

  float clearDepthValue = 0.f;
  float clearStencilValue = 0.f;
  std::array<float, 4> clearColorValue{
      {0.f, 0.f, 0.f, 0.f}};  // double-braces required in C++11
  bool needColorAttachment = true;
  bool depthTestEnabled = false;
  bool stencilTestEnabled = false;
  bool needClearColor = false;
  bool needClearDepth = false;
  bool needClearStencil = false;
  TextureBackend* depthAttachmentTexture = nullptr;
  TextureBackend* stencilAttachmentTexture = nullptr;
  TextureBackend* colorAttachmentsTexture[MAX_COLOR_ATTCHMENT] = {nullptr};
};

}  // namespace backend
}  // namespace april