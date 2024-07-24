
#pragma once

#include <cassert>
#include <functional>

#include "Types.h"
#include "base/Ref.h"

namespace april {
namespace backend {

/**
 * Store texture description.
 */
struct TextureDescriptor {
  TextureType textureType = TextureType::TEXTURE_2D;
  PixelFormat textureFormat = PixelFormat::RGBA8888;
  TextureUsage textureUsage = TextureUsage::READ;
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t depth = 0;
  // 设置纹理采样参数
  SamplerDescriptor samplerDescriptor;
};

class TextureBackend : public Ref {
 public:
  virtual void updateSamplerDescriptor(const SamplerDescriptor& sampler) = 0;

  virtual void getBytes(
      std::size_t x, std::size_t y, std::size_t width, std::size_t height,
      bool flipImage,
      std::function<void(const unsigned char*, std::size_t, std::size_t)>
          callback) = 0;

  virtual void generateMipmaps() = 0;

  virtual void updateTextureDescriptor(const TextureDescriptor& descriptor);

  inline PixelFormat getTextureFormat() const { return _textureFormat; }

  inline TextureUsage getTextureUsage() const { return _textureUsage; }

  inline TextureType getTextureType() const { return _textureType; }

  inline bool hasMipmaps() const { return _hasMipmaps; }

 protected:
  TextureBackend(const TextureDescriptor& descriptor);
  virtual ~TextureBackend();

  uint8_t _bitsPerElement = 0;
  bool _hasMipmaps = false;
  bool _isCompressed = false;
  uint32_t _width = 0;
  uint32_t _height = 0;

  TextureType _textureType = TextureType::TEXTURE_2D;
  PixelFormat _textureFormat = PixelFormat::RGBA8888;
  TextureUsage _textureUsage = TextureUsage::READ;
};

// 2d纹理
class Texture2DBackend : public TextureBackend {
 public:
  virtual void updateData(uint8_t* data, std::size_t width, std::size_t height,
                          std::size_t level) = 0;

  virtual void updateCompressedData(uint8_t* data, std::size_t width,
                                    std::size_t height, std::size_t dataLen,
                                    std::size_t level) = 0;

  virtual void updateSubData(std::size_t xoffset, std::size_t yoffset,
                             std::size_t width, std::size_t height,
                             std::size_t level, uint8_t* data) = 0;

  virtual void updateCompressedSubData(std::size_t xoffset, std::size_t yoffset,
                                       std::size_t width, std::size_t height,
                                       std::size_t dataLen, std::size_t level,
                                       uint8_t* data) = 0;

  inline std::size_t getWidth() const { return _width; }

  inline std::size_t getHeight() const { return _height; }

 protected:
  Texture2DBackend(const TextureDescriptor& descriptor);
};

/**
 * 立方体贴图纹理
 */
class TextureCubemapBackend : public TextureBackend {
 public:
  virtual void updateFaceData(TextureCubeFace side, void* data) = 0;

 protected:
  TextureCubemapBackend(const TextureDescriptor& descriptor);
};

}  // namespace backend
}  // namespace april