
#pragma once

#include <map>
#include <string>
#include <unordered_map>

#include "base/Ref.h"
#include "base/aprilTypes.h"
#include "math/Geometry.h"
#include "renderer/CustomCommand.h"

namespace april {

class Image;
class NinePatchInfo;
class SpriteFrame;
typedef struct _MipmapInfo MipmapInfo;

namespace ui {
class Scale9Sprite;
}

namespace backend {
class Texture2DBackend;
class TextureBackend;
class ProgramState;
}  // namespace backend

class Texture2D : public Ref {
 public:
  struct PixelFormatInfo {
    PixelFormatInfo(int aBpp, bool aCompressed, bool anAlpha)
        : bpp(aBpp), compressed(aCompressed), alpha(anAlpha) {}

    int bpp;
    bool compressed;
    bool alpha;
  };

  typedef std::map<backend::PixelFormat, const PixelFormatInfo>
      PixelFormatInfoMap;

  using TexParams = backend::SamplerDescriptor;

 public:
  static void setDefaultAlphaPixelFormat(backend::PixelFormat format);

  static backend::PixelFormat getDefaultAlphaPixelFormat();

 public:
  Texture2D();

  virtual ~Texture2D();

  /** Initializes with a texture2d with data.*/
  bool initWithData(const void* data, ssize_t dataLen,
                    backend::PixelFormat pixelFormat, int pixelsWide,
                    int pixelsHigh, const Size& contentSize,
                    bool preMultipliedAlpha = false) {
    return initWithData(data, dataLen, pixelFormat, pixelFormat, pixelsWide,
                        pixelsHigh, contentSize, preMultipliedAlpha);
  }

  bool initWithData(const void* data, ssize_t dataLen,
                    backend::PixelFormat pixelFormat,
                    backend::PixelFormat renderFormat, int pixelsWide,
                    int pixelsHigh, const Size& contentSize,
                    bool preMultipliedAlpha = false);

  bool initWithMipmaps(MipmapInfo* mipmaps, int mipmapsNum,
                       backend::PixelFormat pixelFormat,
                       backend::PixelFormat renderFormat, int pixelsWide,
                       int pixelsHigh, bool preMultipliedAlpha = false);

  bool updateWithData(void* data, int offsetX, int offsetY, int width,
                      int height);

  /** Draws a texture at a given point. */
  void drawAtPoint(const glm::vec2& point, float globalZOrder);
  /** Draws a texture inside a rect.*/
  void drawInRect(const Rect& rect, float globalZOrder);

  bool initWithImage(Image* image);

  bool initWithImage(Image* image, backend::PixelFormat format);

  bool initWithString(const char* text, const std::string& fontName,
                      float fontSize, const Size& dimensions = Size(0, 0),
                      TextHAlignment hAlignment = TextHAlignment::CENTER,
                      TextVAlignment vAlignment = TextVAlignment::TOP,
                      bool enableWrap = true, int overflow = 0);

  bool initWithString(const char* text, const FontDefinition& textDefinition);

  bool initWithBackendTexture(backend::TextureBackend* texture,
                              bool preMultipliedAlpha = false);
  void setRenderTarget(bool renderTarget);
  inline bool isRenderTarget() const { return _isRenderTarget; }

  void setTexParameters(const TexParams& params);

  void generateMipmap();

  void setAntiAliasTexParameters();

  void setAliasTexParameters();

  const char* getStringForFormat() const;

  unsigned int getBitsPerPixelForFormat() const;

  unsigned int getBitsPerPixelForFormat(backend::PixelFormat format) const;

  const Size& getContentSizeInPixels();

  /** Whether or not the texture has their Alpha premultiplied. */
  bool hasPremultipliedAlpha() const;

  /** Whether or not the texture has mip maps.*/
  bool hasMipmaps() const;

  /** Gets the pixel format of the texture. */
  backend::PixelFormat getPixelFormat() const;

  /** Gets the width of the texture in pixels. */
  int getPixelsWide() const;

  /** Gets the height of the texture in pixels. */
  int getPixelsHigh() const;

  backend::TextureBackend* getBackendTexture() const;

  /** Gets max S. */
  float getMaxS() const;
  /** Sets max S. */
  void setMaxS(float maxS);

  /** Gets max T. */
  float getMaxT() const;
  /** Sets max T. */
  void setMaxT(float maxT);

  /** Get the texture content size.*/
  Size getContentSize() const;

  std::string getPath() const { return _filePath; }

  void setAlphaTexture(Texture2D* alphaTexture);
  Texture2D* getAlphaTexture() const;

  bool getAlphaTextureName() const;

 public:
  /** Get pixel info map, the key-value pairs is PixelFormat and
   * PixelFormatInfo.*/
  static const PixelFormatInfoMap& getPixelFormatInfoMap();

 private:
  /**
   * A struct for storing 9-patch image capInsets.
   */

  class NinePatchInfo {
   public:
    Rect capInsetSize;
    std::unordered_map<SpriteFrame*, Rect> capInsetMap;
  };

  /**
   * Whether the texture contains a 9-patch capInset info or not.
   *
   * @return True is Texture contains a 9-patch info, false otherwise.
   */
  bool isContain9PatchInfo() const;

  /**
   * Get spriteFrame capInset, If spriteFrame can't be found in 9-patch info
   * map, then single 9-patch texture capInset will be returned. If the arg is
   * nullptr, the capInset of single 9-patch texture will be returned.
   *
   * @param spriteFrame A SpriteFrame object pointer.
   *
   * @return The capInset of the SpriteFrame object.
   */
  const Rect& getSpriteFrameCapInset(SpriteFrame* spriteFrame) const;
  /**
   * Remove the spriteFrame capInset info when the spriteFrame is removed.
   *
   * @param spriteFrame A SpriteFrame object pointer.
   */
  void removeSpriteFrameCapInset(SpriteFrame* spriteFrame);
  /**
   * Add capInset for sprite atlas.
   * When handling single texture, pass nullptr in the first arg.
   *
   * @param spritframe The sprite frame object.
   * @param capInsets The parsed capInset from a .9 patch image.
   */
  void addSpriteFrameCapInset(SpriteFrame* spritframe, const Rect& capInsets);

  void initProgram();

 protected:
  /** pixel format of the texture */
  backend::PixelFormat _pixelFormat;

  /** width in pixels */
  int _pixelsWide;

  /** height in pixels */
  int _pixelsHigh;

  /** texture name */
  backend::Texture2DBackend* _texture;

  /** texture max S */
  float _maxS;

  /** texture max T */
  float _maxT;

  /** content size */
  Size _contentSize;

  /** whether or not the texture has their Alpha premultiplied */
  bool _hasPremultipliedAlpha;

  /** whether or not the texture has mip maps*/
  bool _hasMipmaps;

  static const PixelFormatInfoMap _pixelFormatInfoTables;

  bool _antialiasEnabled;
  NinePatchInfo* _ninePatchInfo;
  friend class SpriteFrameCache;
  friend class TextureCache;
  friend class ui::Scale9Sprite;

  bool _valid;
  std::string _filePath;

  Texture2D* _alphaTexture;
  backend::ProgramState* _programState = nullptr;
  backend::UniformLocation _mvpMatrixLocation;
  backend::UniformLocation _textureLocation;
  CustomCommand _customCommand;

  bool _isRenderTarget = false;
};

}  // namespace april
