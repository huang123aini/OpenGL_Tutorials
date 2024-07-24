/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 11:03:22
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 14:13:06
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/ShaderModule.h
 */

#pragma once

#include <string>

#include "Types.h"
#include "base/BaseMacros.h"
#include "base/Ref.h"

namespace april {
namespace backend {

enum Uniform : uint32_t {
  MVP_MATRIX,
  TEXTURE,
  TEXTURE1,
  TEXTURE2,
  TEXTURE3,
  TEXT_COLOR,
  EFFECT_TYPE,
  EFFECT_COLOR,
  UNIFORM_MAX
};

enum Attribute : uint32_t {
  POSITION,
  COLOR,
  TEXCOORD,
  TEXCOORD1,
  TEXCOORD2,
  TEXCOORD3,
  ATTRIBUTE_MAX
};

class ShaderModule : public april::Ref {
 public:
  /**
   * Get shader stage. The symbolic constant can be either VERTEX or FRAGMENT.
   * @return Shader stage.
   */
  ShaderStage getShaderStage() const;

  std::size_t getHashValue() const { return _hash; }

 protected:
  ShaderModule(ShaderStage stage);
  virtual ~ShaderModule();
  void setHashValue(std::size_t hash) { _hash = hash; }

  friend class ShaderCache;
  ShaderStage _stage = ShaderStage::VERTEX;
  std::size_t _hash = 0;
};

}  // namespace backend
}  // namespace april
