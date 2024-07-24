
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "../Macros.h"
#include "../Program.h"
#include "../RenderPipelineDescriptor.h"
#include "../Types.h"
#include "base/Ref.h"
#include "platform/GL.h"

namespace april {
namespace backend {

class ShaderModuleGL;

/**
 * Store attribute information.
 */
struct AttributeInfo {
  unsigned int location = 0;
  unsigned int size = 0;
  GLenum type = GL_BYTE;
  GLsizei stride = 0;
  unsigned int offset = 0;
  GLboolean needToBeNormallized = GL_FALSE;
  std::string name;
};

/**
 * @addtogroup _opengl
 * @{
 */

/**
 * An OpenGL program.
 */
class ProgramGL : public Program {
 public:
  /**
   * @param vertexShader Specifes the vertex shader source.
   * @param fragmentShader Specifes the fragment shader source.
   */
  ProgramGL(const std::string& vertexShader, const std::string& fragmentShader);

  ~ProgramGL();

  /**
   * Get attribute informations.
   * @return Attribute informations.
   */
  inline const std::vector<AttributeInfo>& getAttributeInfos() const {
    return _attributeInfos;
  }

  /**
   * Get program object.
   * @return Program object.
   */
  inline GLuint getHandler() const { return _program; }

  /**
   * Calculate attribute information according to vertex layout.
   */
  void computeAttributeInfos(const RenderPipelineDescriptor& descriptor);

  /**
   * Get uniform location by name.
   * @param uniform Specifies the uniform name.
   * @return The uniform location.
   */
  virtual UniformLocation getUniformLocation(
      const std::string& uniform) const override;

  /**
   * Get uniform location by engine built-in uniform enum name.
   * @param name Specifies the engine built-in uniform enum name.
   * @return The uniform location.
   */
  virtual UniformLocation getUniformLocation(
      backend::Uniform name) const override;

  /**
   * Get attribute location by attribute name.
   * @param name Specifies the attribute name.
   * @return The attribute location.
   */
  virtual int getAttributeLocation(const std::string& name) const override;

  /**
   * Get attribute location by engine built-in attribute enum name.
   * @param name Specifies the engine built-in attribute enum name.
   * @return The attribute location.
   */
  virtual int getAttributeLocation(Attribute name) const override;

  /**
   * Get maximum vertex location.
   * @return Maximum vertex locaiton.
   */
  virtual int getMaxVertexLocation() const override;

  /**
   * Get maximum fragment location.
   * @return Maximum fragment location.
   */
  virtual int getMaxFragmentLocation() const override;

  /**
   * Get active vertex attributes.
   * @return Active vertex attributes. key is active attribute name, Value is
   * corresponding attribute info.
   */
  virtual const std::unordered_map<std::string, AttributeBindInfo>
  getActiveAttributes() const override;

  /**
   * Get uniform buffer size in bytes that can hold all the uniforms.
   * @param stage Specifies the shader stage. The symbolic constant can be
   * either VERTEX or FRAGMENT.
   * @return The uniform buffer size in bytes.
   */
  virtual std::size_t getUniformBufferSize(ShaderStage stage) const override;

  /**
   * Get a uniformInfo in given location from the specific shader stage.
   * @param stage Specifies the shader stage. The symbolic constant can be
   * either VERTEX or FRAGMENT.
   * @param location Specifies the uniform locaion.
   * @return The uniformInfo.
   */
  virtual const UniformInfo& getActiveUniformInfo(ShaderStage stage,
                                                  int location) const override;

  /**
   * Get all uniformInfos.
   * @return The uniformInfos.
   */
  virtual const std::unordered_map<std::string, UniformInfo>&
  getAllActiveUniformInfo(ShaderStage stage) const override;

 private:
  void compileProgram();
  bool getAttributeLocation(const std::string& attributeName,
                            unsigned int& location) const;
  void computeUniformInfos();
  void computeLocations();
#if CC_ENABLE_CACHE_TEXTURE_DATA
  virtual void reloadProgram();
  virtual int getMappedLocation(int location) const override;
  virtual int getOriginalLocation(int location) const override;
  virtual const std::unordered_map<std::string, int> getAllUniformsLocation()
      const override {
    return _originalUniformLocations;
  }
#endif

  GLuint _program = 0;
  ShaderModuleGL* _vertexShaderModule = nullptr;
  ShaderModuleGL* _fragmentShaderModule = nullptr;

  std::vector<AttributeInfo> _attributeInfos;
  std::unordered_map<std::string, UniformInfo> _activeUniformInfos;
#if CC_ENABLE_CACHE_TEXTURE_DATA
  std::unordered_map<std::string, int>
      _originalUniformLocations;  ///< record the uniform location when shader
                                  ///< was first created.
  std::unordered_map<int, int> _mapToCurrentActiveLocation;  ///<
  std::unordered_map<int, int> _mapToOriginalLocation;       ///<
  EventListenerCustom* _backToForegroundListener = nullptr;
#endif

  std::size_t _totalBufferSize = 0;
  int _maxLocation = -1;
  UniformLocation _builtinUniformLocation[UNIFORM_MAX];
  int _builtinAttributeLocation[Attribute::ATTRIBUTE_MAX];
  std::unordered_map<int, int> _bufferOffset;
};

}  // namespace backend
}  // namespace april