/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 10:10:27
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 10:14:04
 * @FilePath: /OpenGL_Tutorials/renderer/backend/ProgramCache.h
 */

#pragma once

#include <string>
#include <unordered_map>

#include "Program.h"
#include "base/Ref.h"

namespace april {
namespace backend {

class ProgramCache : public Ref {
 public:
  static ProgramCache* getInstance();

  static void destroyInstance();

  backend::Program* getBuiltinProgram(ProgramType type) const;

  void removeProgram(backend::Program* program);

  void removeUnusedProgram();

  void removeAllPrograms();

  void addCustomProgram(const std::string& key, backend::Program* program);

  backend::Program* getCustomProgram(const std::string& key) const;

 protected:
  ProgramCache() = default;
  virtual ~ProgramCache();

  bool init();

  void addProgram(ProgramType type);

  static std::unordered_map<backend::ProgramType, backend::Program*>
      cached_programs_;
  static std::unordered_map<std::string, backend::Program*>
      cached_custom_programs_;
  static ProgramCache* shared_program_cache_;
};

}  // namespace backend
}  // namespace april