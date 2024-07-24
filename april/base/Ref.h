/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 09:17:56
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-24 10:01:01
 * @FilePath: /OpenGL_Tutorials/base/Ref.h
 */
#pragma once

namespace april {

class Ref {
 public:
  void retain();

  void release();

  Ref* autorelease();

  unsigned int getReferenceCount() const;

 protected:
  Ref();

 public:
  virtual ~Ref();

 protected:
  unsigned int reference_count_;
};

}  // namespace april
