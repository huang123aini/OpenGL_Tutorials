/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 10:02:43
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 10:09:37
 * @FilePath: /OpenGL_Tutorials/renderer/backend/Program.cpp
 */

#include "Program.h"

#include "ProgramCache.h"

namespace april {
namespace backend {

Program::Program(const std::string& vs, const std::string& fs)
    : vertex_shader_(vs), fragment_shader_(fs) {}

void Program::setProgramType(ProgramType type) { program_type_ = type; }

Program* Program::getBuiltinProgram(ProgramType type) {
  return ProgramCache::getInstance()->getBuiltinProgram(type);
}

}  // namespace backend
}  // namespace april
