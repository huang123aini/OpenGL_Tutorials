/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-24 10:02:43
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-24 10:05:45
 * @FilePath: /OpenGL_Tutorials/april/base/AutoreleasePool.h
 */

#pragma once

#include <string>
#include <vector>

#include "base/Ref.h"

namespace april {

class AutoreleasePool {
 public:
  AutoreleasePool();

  AutoreleasePool(const std::string& name);

  ~AutoreleasePool();

  void addObject(Ref* object);

  void clear();

#if defined(APRIL_DEBUG) && (APRIL_DEBUG > 0)
  bool isClearing() const { return _isClearing; };
#endif

  bool contains(Ref* object) const;

  void dump();

 private:
  std::vector<Ref*> _managedObjectArray;
  std::string _name;

#if defined(APRIL_DEBUG) && (APRIL_DEBUG > 0)
  bool _isClearing;
#endif
};

class PoolManager {
 public:
  static PoolManager* getInstance();
  static void destroyInstance();

  /**
   * Get current auto release pool, there is at least one auto release pool that
   * created by engine. You can create your own auto release pool at demand,
   * which will be put into auto release pool stack.
   */
  AutoreleasePool* getCurrentPool() const;

  bool isObjectInPools(Ref* obj) const;

  friend class AutoreleasePool;

 private:
  PoolManager();
  ~PoolManager();

  void push(AutoreleasePool* pool);
  void pop();

  static PoolManager* s_singleInstance;

  std::vector<AutoreleasePool*> _releasePoolStack;
};

}  // namespace april