/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 16:27:06
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 16:27:26
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/opengl/ShaderModuleGL.h
 */

#pragma once

#include "../ShaderModule.h"
#include "platform/GL.h"

namespace april {
namespace backend {

/**
 * @addtogroup _opengl
 * @{
 */

/**
 * Create and compile shader.
 */
class ShaderModuleGL : public ShaderModule {
 public:
  /**
   * @param stage Specifies whether is vertex shader or fragment shader.
   * @param source Specifies shader source.
   */
  ShaderModuleGL(ShaderStage stage, const std::string& source);
  ~ShaderModuleGL();

  /**
   * Get shader object.
   * @return Shader object.
   */
  inline GLuint getShader() const { return _shader; }

 private:
  void compileShader(ShaderStage stage, const std::string& source);
  char* getErrorLog(GLuint shader) const;
  void deleteShader();

  GLuint _shader = 0;
  friend class ProgramGL;
};
}  // namespace backend
}  // namespace april