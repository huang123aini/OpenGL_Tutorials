/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 16:27:16
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-24 09:38:51
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/opengl/ShaderModuleGL.cpp
 */

#include "ShaderModuleGL.h"

#include "base/BaseMacros.h"
// #include "platform/PlatformMacros.h"

namespace april {
namespace backend {

ShaderModuleGL::ShaderModuleGL(ShaderStage stage, const std::string& source)
    : ShaderModule(stage) {
  compileShader(stage, source);
}

ShaderModuleGL::~ShaderModuleGL() { deleteShader(); }

void ShaderModuleGL::compileShader(ShaderStage stage,
                                   const std::string& source) {
  GLenum shaderType =
      stage == ShaderStage::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
  const GLchar* sourcePtr = reinterpret_cast<const GLchar*>(source.c_str());
  _shader = glCreateShader(shaderType);
  if (!_shader) return;

  glShaderSource(_shader, 1, &sourcePtr, nullptr);
  glCompileShader(_shader);

  GLint status = 0;
  glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
  if (!status) {
    printf("cocos2d: ERROR: Failed to compile shader:\n%s", source.c_str());
    printf("cocos2d: %s", getErrorLog(_shader));
    deleteShader();
    assert(false);
  }
}

char* ShaderModuleGL::getErrorLog(GLuint shader) const {
  GLint logLength = 0;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
  char* log = (char*)malloc(sizeof(char) * logLength);
  glGetShaderInfoLog(shader, logLength, nullptr, log);
  return log;
}

void ShaderModuleGL::deleteShader() {
  if (_shader) {
    glDeleteShader(_shader);
    _shader = 0;
  }
}

}  // namespace backend
}  // namespace april