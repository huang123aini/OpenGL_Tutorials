/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-24 14:20:20
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-24 14:24:46
 * @FilePath: /OpenGL_Tutorials/april/renderer/TextureCube.h
 */

#include <string>
#include <unordered_map>

#include "base/aprilTypes.h"
#include "renderer/Texture2D.h"
#include "renderer/backend/Texture.h"

namespace april {

class TextureCube : public Ref {
 public:
  /** create cube texture from 6 textures.
     @param positive_x texture for the right side of the texture cube face.
     @param negative_x texture for the up side of the texture cube face.
     @param positive_y texture for the top side of the texture cube face
     @param negative_y texture for the bottom side of the texture cube face
     @param positive_z texture for the forward side of the texture cube face.
     @param negative_z texture for the rear side of the texture cube face.
     @return  A new texture cube inited with given parameters.
  */
  static TextureCube* create(const std::string& positive_x,
                             const std::string& negative_x,
                             const std::string& positive_y,
                             const std::string& negative_y,
                             const std::string& positive_z,
                             const std::string& negative_z);

  void setTexParameters(const Texture2D::TexParams&);

  backend::TextureBackend* getBackendTexture() { return _texture; }

  bool reloadTexture();

 public:
  TextureCube();

  virtual ~TextureCube();

 protected:
  bool init(const std::string& positive_x, const std::string& negative_x,
            const std::string& positive_y, const std::string& negative_y,
            const std::string& positive_z, const std::string& negative_z);

 private:
  std::vector<std::string> _imgPath;
  backend::TextureCubemapBackend* _texture = nullptr;
};

}  // namespace april