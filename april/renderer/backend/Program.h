/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 10:02:36
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 14:19:52
 * @FilePath: /OpenGL_Tutorials/renderer/backend/Program.h
 */

#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "base/Ref.h"
#include "renderer/backend/ShaderCache.h"
#include "renderer/backend/Types.h"

namespace april {
namespace backend {

class ShaderModule;

class Program : public Ref {
 public:
  static Program* getBuiltinProgram(ProgramType type);

  virtual UniformLocation getUniformLocation(
      const std::string& uniform) const = 0;

  virtual UniformLocation getUniformLocation(backend::Uniform name) const = 0;

  virtual int getAttributeLocation(const std::string& name) const = 0;

  virtual int getAttributeLocation(backend::Attribute name) const = 0;

  virtual int getMaxVertexLocation() const = 0;

  virtual int getMaxFragmentLocation() const = 0;

  virtual const std::unordered_map<std::string, AttributeBindInfo>
  getActiveAttributes() const = 0;

  const std::string& getVertexShader() const { return vertex_shader_; }

  const std::string& getFragmentShader() const { return fragment_shader_; }

  ProgramType getProgramType() const { return program_type_; }

  virtual std::size_t getUniformBufferSize(ShaderStage stage) const = 0;

  virtual const UniformInfo& getActiveUniformInfo(ShaderStage stage,
                                                  int location) const = 0;

  virtual const std::unordered_map<std::string, UniformInfo>&
  getAllActiveUniformInfo(ShaderStage stage) const = 0;

 protected:
  void setProgramType(ProgramType type);

  Program(const std::string& vs, const std::string& fs);

  friend class ProgramCache;

  std::string vertex_shader_;    ///< Vertex shader.
  std::string fragment_shader_;  ///< Fragment shader.
  ProgramType program_type_ = ProgramType::CUSTOM_PROGRAM;
};

}  // namespace backend
}  // namespace april
