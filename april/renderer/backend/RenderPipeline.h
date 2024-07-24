/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 11:19:45
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-24 11:14:06
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/RenderPipeline.h
 */

#pragma once

#include "Macros.h"
#include "Types.h"
#include "base/Ref.h"
#include "renderer/PipelineDescriptor.h"
#include "renderer/backend/RenderPassDescriptor.h"

namespace april {
namespace backend {
/**
 * @addtogroup _backend
 * @{
 */

/**
 * Render pipeline
 */
class RenderPipeline : public april::Ref {
 public:
  virtual void update(const PipelineDescriptor& pipelineDescirptor,
                      const RenderPassDescriptor& renderpassDescriptor) = 0;

 protected:
  virtual ~RenderPipeline() = default;
};
}  // namespace backend
}  // namespace april