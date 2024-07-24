/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 11:21:11
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 11:21:22
 * @FilePath:
 * /OpenGL_Tutorials/april/renderer/backend/RenderPipelineDescriptor.h
 */

#pragma once

#include <memory>
#include <vector>

#include "Macros.h"
#include "Types.h"
#include "VertexLayout.h"
#include "renderer/backend/ProgramState.h"

namespace april {
namespace backend {

class DepthStencilState;
class BlendState;
/**
 * @addtogroup _backend
 * @{
 */

/**
 * Store values about pipeline.
 * 存储渲染管线的值
 */
struct RenderPipelineDescriptor {
  ProgramState* programState = nullptr;
  BlendState* blendState = nullptr;
  PixelFormat colorAttachmentsFormat[MAX_COLOR_ATTCHMENT] = {
      PixelFormat::DEFAULT};
  PixelFormat depthAttachmentFormat = PixelFormat::NONE;
  PixelFormat stencilAttachmentFormat = PixelFormat::NONE;
};

}  // namespace backend
}  // namespace april
