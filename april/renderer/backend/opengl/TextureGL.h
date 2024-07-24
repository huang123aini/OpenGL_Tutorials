
#pragma once

#include "../Texture.h"
#include "platform/GL.h"

namespace april {
namespace backend {

/**
 * Store texture information.
 */
struct TextureInfoGL {
  void applySamplerDescriptor(const SamplerDescriptor& desc, bool isPow2,
                              bool hasMipmaps);

  GLint magFilterGL = GL_LINEAR;
  GLint minFilterGL = GL_LINEAR;
  GLint sAddressModeGL = GL_REPEAT;
  GLint tAddressModeGL = GL_REPEAT;

  // Used in glTexImage2D().
  GLint internalFormat = GL_RGBA;
  GLenum format = GL_RGBA;
  GLenum type = GL_UNSIGNED_BYTE;

  GLuint texture = 0;
};

class Texture2DGL : public backend::Texture2DBackend {
 public:
  /**
   * @param descirptor Specifies the texture description.
   */
  Texture2DGL(const TextureDescriptor& descriptor);
  ~Texture2DGL();

  virtual void updateData(uint8_t* data, std::size_t width, std::size_t height,
                          std::size_t level) override;

  virtual void updateCompressedData(uint8_t* data, std::size_t width,
                                    std::size_t height, std::size_t dataLen,
                                    std::size_t level) override;

  virtual void updateSubData(std::size_t xoffset, std::size_t yoffset,
                             std::size_t width, std::size_t height,
                             std::size_t level, uint8_t* data) override;

  virtual void updateCompressedSubData(std::size_t xoffset, std::size_t yoffset,
                                       std::size_t width, std::size_t height,
                                       std::size_t dataLen, std::size_t level,
                                       uint8_t* data) override;

  virtual void updateSamplerDescriptor(
      const SamplerDescriptor& sampler) override;

  virtual void getBytes(
      std::size_t x, std::size_t y, std::size_t width, std::size_t height,
      bool flipImage,
      std::function<void(const unsigned char*, std::size_t, std::size_t)>
          callback) override;

  virtual void generateMipmaps() override;

  virtual void updateTextureDescriptor(
      const TextureDescriptor& descriptor) override;

  inline GLuint getHandler() const { return _textureInfo.texture; }

  void apply(int index) const;

 private:
  void initWithZeros();

  TextureInfoGL _textureInfo;
};

/**
 * Texture cube.
 */
class TextureCubeGL : public backend::TextureCubemapBackend {
 public:
  /**
   * @param descirptor Specifies the texture description.
   */
  TextureCubeGL(const TextureDescriptor& descriptor);
  ~TextureCubeGL();

  /**
   * Update sampler
   * @param sampler Specifies the sampler descriptor.
   */
  virtual void updateSamplerDescriptor(
      const SamplerDescriptor& sampler) override;

  /**
   * Update texutre cube data in give slice side.
   * @param side Specifies which slice texture of cube to be update.
   * @param data Specifies a pointer to the image data in memory.
   */
  virtual void updateFaceData(TextureCubeFace side, void* data) override;

  /**
   * Read a block of pixels from the drawable texture
   * @param x,y Specify the window coordinates of the first pixel that is read
   * from the drawable texture. This location is the lower left corner of a
   * rectangular block of pixels.
   * @param width,height Specify the dimensions of the pixel rectangle. width
   * and height of one correspond to a single pixel.
   * @param flipImage Specifies if needs to flip the image.
   * @param callback
   */
  virtual void getBytes(
      std::size_t x, std::size_t y, std::size_t width, std::size_t height,
      bool flipImage,
      std::function<void(const unsigned char*, std::size_t, std::size_t)>
          callback) override;

  /// Generate mipmaps.
  virtual void generateMipmaps() override;

  /**
   * Update texture description.
   * @param descriptor Specifies texture and sampler descriptor.
   */
  virtual void updateTextureDescriptor(
      const TextureDescriptor& descriptor) override;

  /**
   * Get texture object.
   * @return Texture object.
   */
  inline GLuint getHandler() const { return _textureInfo.texture; }

  /**
   * Set texture to pipeline
   * @param index Specifies the texture image unit selector.
   */
  void apply(int index) const;

 private:
  void setTexParameters();

  TextureInfoGL _textureInfo;
};

}  // namespace backend
}  // namespace april
