/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 09:18:03
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-24 10:08:25
 * @FilePath: /OpenGL_Tutorials/base/Ref.cpp
 */

#include "Ref.h"

#include <assert.h>

#include "base/AutoreleasePool.h"

namespace april {
Ref::Ref() : reference_count_(1) {}

Ref::~Ref() {}

void Ref::retain() {
  assert(reference_count_ > 0);
  ++reference_count_;
}

void Ref::release() {
  assert(reference_count_ > 0);
  --reference_count_;

  if (reference_count_ == 0) {
    delete this;
  }
}

Ref* Ref::autorelease() {
  PoolManager::getInstance()->getCurrentPool()->addObject(this);
  return this;
}

unsigned int Ref::getReferenceCount() const { return reference_count_; }

}  // namespace april