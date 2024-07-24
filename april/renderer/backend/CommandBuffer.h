/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 13:07:18
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 14:45:30
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/CommandBuffer.h
 */

#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "Macros.h"
#include "ProgramState.h"
#include "RenderPassDescriptor.h"
#include "Types.h"
#include "VertexLayout.h"
#include "base/Ref.h"

namespace april {
namespace backend {

class RenderPass;
class RenderPipeline;
class Buffer;
class DepthStencilState;

class CommandBuffer : public april::Ref {
 public:
  virtual void beginFrame() = 0;

  /**
   * Begin a render pass, initial color, depth and stencil attachment.
   */
  virtual void beginRenderPass(const RenderPassDescriptor& descriptor) = 0;

  virtual void setRenderPipeline(RenderPipeline* renderPipeline) = 0;

  virtual void setViewport(int x, int y, unsigned int w, unsigned int h) = 0;

  virtual void setCullMode(CullMode mode) = 0;

  virtual void setWinding(Winding winding) = 0;

  virtual void setVertexBuffer(Buffer* buffer) = 0;

  virtual void setProgramState(ProgramState* programState) = 0;

  virtual void setIndexBuffer(Buffer* buffer) = 0;

  virtual void drawArrays(PrimitiveType primitiveType, std::size_t start,
                          std::size_t count) = 0;

  virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType,
                            std::size_t count, std::size_t offset) = 0;

  virtual void endRenderPass() = 0;

  virtual void endFrame() = 0;

  virtual void setLineWidth(float lineWidth) = 0;

  virtual void setScissorRect(bool isEnabled, float x, float y, float width,
                              float height) = 0;

  virtual void setDepthStencilState(DepthStencilState* depthStencilState) = 0;

  virtual void captureScreen(
      std::function<void(const unsigned char*, int, int)> callback) = 0;

  void setStencilReferenceValue(unsigned int value);

  void setStencilReferenceValue(unsigned int frontRef, unsigned int backRef);

 protected:
  virtual ~CommandBuffer() = default;

  unsigned int _stencilReferenceValueFront =
      0;  ///< front stencil reference value.
  unsigned int _stencilReferenceValueBack =
      0;  ///< back stencil reference value.
};

}  // namespace backend
}  // namespace april