/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 11:03:31
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 14:13:24
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/ShaderModule.cpp
 */

#include "renderer/backend/ShaderModule.h"

namespace april {
namespace backend {

ShaderStage ShaderModule::getShaderStage() const { return _stage; }

ShaderModule::ShaderModule(ShaderStage stage) : _stage(stage) {}

ShaderModule::~ShaderModule() {}

}  // namespace backend
}  // namespace april
