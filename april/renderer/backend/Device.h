
#pragma once

#include <string>

#include "DepthStencilState.h"
#include "DeviceInfo.h"
#include "Macros.h"
#include "ProgramCache.h"
#include "RenderPassDescriptor.h"
#include "RenderPipelineDescriptor.h"
#include "ShaderCache.h"
#include "Texture.h"
#include "Types.h"
#include "base/Ref.h"

namespace april {
namespace backend {

class CommandBuffer;
class Buffer;
class ShaderModule;
class RenderPipeline;
class RenderPass;

class Device : public april::Ref {
 public:
  friend class ProgramCache;
  friend class ShaderCache;

  static Device* getInstance();

  virtual ~Device() = default;

  /**
   * New a CommandBuffer object, not auto released.
   * @return A CommandBuffer object.
   */
  virtual CommandBuffer* newCommandBuffer() = 0;

  /**
   * New a Buffer object, not auto released.
   * @param size Specifies the size in bytes of the buffer object's new data
   * store.
   * @param type Specifies the target buffer object. The symbolic constant must
   * be BufferType::VERTEX or BufferType::INDEX.
   * @param usage Specifies the expected usage pattern of the data store. The
   * symbolic constant must be BufferUsage::STATIC, BufferUsage::DYNAMIC.
   * @return A Buffer object.
   */
  virtual Buffer* newBuffer(size_t size, BufferType type,
                            BufferUsage usage) = 0;

  /**
   * New a TextureBackend object, not auto released.
   * @param descriptor Specifies texture description.
   * @return A TextureBackend object.
   */
  virtual TextureBackend* newTexture(const TextureDescriptor& descriptor) = 0;

  /**
   * Create an auto released DepthStencilState object.
   * @param descriptor Specifies depth and stencil description.
   * @return An auto release DepthStencilState object.
   */
  virtual DepthStencilState* createDepthStencilState(
      const DepthStencilDescriptor& descriptor) = 0;

  /**
   * New a RenderPipeline object, not auto released.
   * @param descriptor Specifies render pipeline description.
   * @return A RenderPipeline object.
   */
  virtual RenderPipeline* newRenderPipeline() = 0;

  /**
   * This property controls whether or not the drawables'
   * metal textures may only be used for framebuffer attachments (YES) or
   * whether they may also be used for texture sampling and pixel
   * read/write operations (NO).
   * @param frameBufferOnly A value of YES allows CAMetalLayer to allocate the
   * MTLTexture objects in ways that are optimized for display purposes that
   * makes them unsuitable for sampling. The recommended value for most
   * applications is YES.
   * @note This interface is specificaly designed for metal.
   */
  virtual void setFrameBufferOnly(bool frameBufferOnly) = 0;

  virtual Program* newProgram(const std::string& vertexShader,
                              const std::string& fragmentShader) = 0;

  inline DeviceInfo* getDeviceInfo() const { return _deviceInfo; }

 protected:
  virtual ShaderModule* newShaderModule(ShaderStage stage,
                                        const std::string& source) = 0;

  DeviceInfo* _deviceInfo = nullptr;  ///< Device information.

 private:
  static Device* _instance;
};

}  // namespace backend
}  // namespace april
