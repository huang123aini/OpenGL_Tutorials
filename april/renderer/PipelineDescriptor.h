/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 13:21:21
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-24 09:49:21
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/PipelineDescriptor.h
 */

#pragma once

#include <string>

// #include "platform/CCPlatformMacros.h"
#include "renderer/backend/DepthStencilState.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/RenderPassDescriptor.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/VertexLayout.h"

namespace april {

struct PipelineDescriptor {
  backend::ProgramState* programState = nullptr;
  backend::BlendDescriptor blendDescriptor;
};
}  // namespace april
