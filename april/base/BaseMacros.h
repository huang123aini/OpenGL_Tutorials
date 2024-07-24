/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 10:31:23
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-24 11:12:49
 * @FilePath: /OpenGL_Tutorials/base/Macros.h
 */

#define SAFE_DELETE(p) \
  do {                 \
    delete (p);        \
    (p) = nullptr;     \
  } while (0)

#define SAFE_DELETE_ARRAY(p) \
  do {                       \
    if (p) {                 \
      delete[] (p);          \
      (p) = nullptr;         \
    }                        \
  } while (0)

#define SAFE_FREE(p) \
  do {               \
    if (p) {         \
      free(p);       \
      (p) = nullptr; \
    }                \
  } while (0)

#define SAFE_RELEASE(p) \
  do {                  \
    if (p) {            \
      (p)->release();   \
    }                   \
  } while (0)

#define SAFE_RELEASE_NULL(p) \
  do {                       \
    if (p) {                 \
      (p)->release();        \
      (p) = nullptr;         \
    }                        \
  } while (0)

#define SAFE_RETAIN(p) \
  do {                 \
    if (p) {           \
      (p)->retain();   \
    }                  \
  } while (0)

#define BREAK_IF(cond) \
  if (cond) break

/****************opengl*****************/

// 默认打开测试
#define APRIL_DEBUG 1

#if !defined(APRIL_DEBUG) || APRIL_DEBUG == 0
#define CHECK_GL_ERROR_DEBUG()
#else
#define CHECK_GL_ERROR_DEBUG()                                       \
  do {                                                               \
    GLenum __error = glGetError();                                   \
    if (__error) {                                                   \
      printf("OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, \
             __FUNCTION__, __LINE__);                                \
    }                                                                \
  } while (false)
#define CHECK_GL_ERROR_ABORT()                                       \
  do {                                                               \
    GLenum __error = glGetError();                                   \
    if (__error) {                                                   \
      printf("OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, \
             __FUNCTION__, __LINE__);                                \
      assert(false);                                                 \
    }                                                                \
  } while (false)
#endif

/******************Math**************************/

#ifndef FLT_EPSILON
#define FLT_EPSILON 1.192092896e-07F
#endif  // FLT_EPSILON