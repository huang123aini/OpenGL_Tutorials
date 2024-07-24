/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 16:25:21
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-24 10:11:57
 * @FilePath:
 * /OpenGL_Tutorials/april/renderer/backend/opengl/RenderPipelineGL.cpp
 */

#include "RenderPipelineGL.h"

#include <assert.h>

#include "DepthStencilStateGL.h"
#include "ProgramGL.h"
#include "ShaderModuleGL.h"
#include "UtilsGL.h"

namespace april {

namespace backend {

void RenderPipelineGL::update(
    const PipelineDescriptor& pipelineDescirptor,
    const RenderPassDescriptor& renderpassDescriptor) {
  if (_programGL != pipelineDescirptor.programState->getProgram()) {
    SAFE_RELEASE(_programGL);
    _programGL =
        static_cast<ProgramGL*>(pipelineDescirptor.programState->getProgram());
    SAFE_RETAIN(_programGL);
  }

  updateBlendState(pipelineDescirptor.blendDescriptor);
}

void RenderPipelineGL::updateBlendState(const BlendDescriptor& descriptor) {
  auto blendEnabled = descriptor.blendEnabled;
  auto rgbBlendOperation =
      UtilsGL::toGLBlendOperation(descriptor.rgbBlendOperation);
  auto alphaBlendOperation =
      UtilsGL::toGLBlendOperation(descriptor.alphaBlendOperation);
  auto sourceRGBBlendFactor =
      UtilsGL::toGLBlendFactor(descriptor.sourceRGBBlendFactor);
  auto destinationRGBBlendFactor =
      UtilsGL::toGLBlendFactor(descriptor.destinationRGBBlendFactor);
  auto sourceAlphaBlendFactor =
      UtilsGL::toGLBlendFactor(descriptor.sourceAlphaBlendFactor);
  auto destinationAlphaBlendFactor =
      UtilsGL::toGLBlendFactor(descriptor.destinationAlphaBlendFactor);
  auto writeMaskRed =
      (uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::RED;
  auto writeMaskGreen =
      (uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::GREEN;
  auto writeMaskBlue =
      (uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::BLUE;
  auto writeMaskAlpha =
      (uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::ALPHA;

  if (blendEnabled) {
    glEnable(GL_BLEND);
    glBlendEquationSeparate(rgbBlendOperation, alphaBlendOperation);
    glBlendFuncSeparate(sourceRGBBlendFactor, destinationRGBBlendFactor,
                        sourceAlphaBlendFactor, destinationAlphaBlendFactor);
  } else
    glDisable(GL_BLEND);

  glColorMask(writeMaskRed, writeMaskGreen, writeMaskBlue, writeMaskAlpha);
}

RenderPipelineGL::~RenderPipelineGL() { SAFE_RELEASE(_programGL); }

}  // namespace backend
}  // namespace april
