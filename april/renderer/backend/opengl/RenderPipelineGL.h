/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 16:24:57
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 16:25:38
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/opengl/RenderPipelineGL.h
 */

#pragma once

#include <vector>

#include "../RenderPipeline.h"
#include "../RenderPipelineDescriptor.h"
#include "platform/GL.h"

namespace april {
namespace backend {

class ProgramGL;

class RenderPipelineGL : public RenderPipeline {
 public:
  /**
   * @param descriptor Specifies render pipeline descriptor.
   */
  RenderPipelineGL() = default;
  ~RenderPipelineGL();

  virtual void update(
      const PipelineDescriptor& pipelineDescirptor,
      const RenderPassDescriptor& renderpassDescriptor) override;
  /**
   * Get program instance.
   * @return Program instance.
   */
  inline ProgramGL* getProgram() const { return _programGL; }

 private:
  void updateBlendState(const BlendDescriptor& descriptor);

  ProgramGL* _programGL = nullptr;
};
}  // namespace backend
}  // namespace april