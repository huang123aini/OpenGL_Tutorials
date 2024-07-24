/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 10:56:36
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 14:50:44
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/ShaderCache.cpp
 */

#include "renderer/backend/ShaderCache.h"

#include <iostream>

#include "renderer/backend/Device.h"

namespace april {
namespace backend {

std::unordered_map<std::size_t, backend::ShaderModule*>
    ShaderCache::_cachedShaders;
ShaderCache* ShaderCache::_sharedShaderCache = nullptr;

ShaderCache* ShaderCache::getInstance() {
  if (!_sharedShaderCache) {
    _sharedShaderCache = new (std::nothrow) ShaderCache();
    if (!_sharedShaderCache->init()) {
      SAFE_RELEASE(_sharedShaderCache);
    }
  }
  return _sharedShaderCache;
}

void ShaderCache::destroyInstance() { SAFE_RELEASE_NULL(_sharedShaderCache); }

ShaderCache::~ShaderCache() {
  for (auto& shaderModule : _cachedShaders) {
    SAFE_RELEASE(shaderModule.second);
  }
  std::cout << "deallocing ProgramCache: " << this << std::endl;
}

bool ShaderCache::init() { return true; }

backend::ShaderModule* ShaderCache::newVertexShaderModule(
    const std::string& shaderSource) {
  auto vertexShaderModule =
      newShaderModule(backend::ShaderStage::VERTEX, shaderSource);
  return vertexShaderModule;
}

backend::ShaderModule* ShaderCache::newFragmentShaderModule(
    const std::string& shaderSource) {
  auto fragmenShaderModule =
      newShaderModule(backend::ShaderStage::FRAGMENT, shaderSource);
  return fragmenShaderModule;
}

backend::ShaderModule* ShaderCache::newShaderModule(
    backend::ShaderStage stage, const std::string& shaderSource) {
  std::size_t key = std::hash<std::string>{}(shaderSource);
  auto iter = _cachedShaders.find(key);
  if (_cachedShaders.end() != iter) return iter->second;

  auto shader =
      backend::Device::getInstance()->newShaderModule(stage, shaderSource);
  shader->setHashValue(key);
  _cachedShaders.emplace(key, shader);

  return shader;
}

void ShaderCache::removeUnusedShader() {
  for (auto iter = _cachedShaders.cbegin(); iter != _cachedShaders.cend();) {
    auto shaderModule = iter->second;
    if (shaderModule->getReferenceCount() == 1) {
      shaderModule->release();
      iter = _cachedShaders.erase(iter);
    } else {
      ++iter;
    }
  }
}

}  // namespace backend
}  // namespace april
