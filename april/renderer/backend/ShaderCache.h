/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 10:56:27
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 14:13:54
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/ShaderCache.h
 */

#pragma once

#include <string>
#include <unordered_map>

#include "base/BaseMacros.h"
#include "base/Ref.h"
#include "renderer/backend/ShaderModule.h"

namespace april {
namespace backend {

class ShaderCache : public Ref {
 public:
  static ShaderCache* getInstance();

  static void destroyInstance();

  static backend::ShaderModule* newVertexShaderModule(
      const std::string& shaderSource);

  static backend::ShaderModule* newFragmentShaderModule(
      const std::string& shaderSource);

  void removeUnusedShader();

 protected:
  virtual ~ShaderCache();

  bool init();

  static backend::ShaderModule* newShaderModule(
      backend::ShaderStage stage, const std::string& shaderSource);

  static std::unordered_map<std::size_t, backend::ShaderModule*> _cachedShaders;
  static ShaderCache* _sharedShaderCache;
};

}  // namespace backend
}  // namespace april
