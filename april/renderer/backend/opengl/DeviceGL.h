/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 16:10:03
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 16:11:26
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/opengl/DeviceGL.h
 */

#include "../Device.h"

namespace april {
namespace backend {

class DeviceGL : public Device {
 public:
  DeviceGL();
  ~DeviceGL();

  virtual CommandBuffer* newCommandBuffer() override;

  virtual Buffer* newBuffer(std::size_t size, BufferType type,
                            BufferUsage usage) override;

  virtual TextureBackend* newTexture(
      const TextureDescriptor& descriptor) override;

  virtual DepthStencilState* createDepthStencilState(
      const DepthStencilDescriptor& descriptor) override;

  virtual RenderPipeline* newRenderPipeline() override;

  virtual void setFrameBufferOnly(bool frameBufferOnly) override {}

  virtual Program* newProgram(const std::string& vertexShader,
                              const std::string& fragmentShader) override;

 protected:
  virtual ShaderModule* newShaderModule(ShaderStage stage,
                                        const std::string& source) override;
};

}  // namespace backend
}  // namespace april