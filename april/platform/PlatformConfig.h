/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 10:49:41
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 10:53:10
 * @FilePath: /OpenGL_Tutorials/april/platform/PlatformConfig.h
 */

#define PLATFORM_UNKNOWN 0
#define PLATFORM_IOS 1
#define PLATFORM_ANDROID 2
#define PLATFORM_WIN32 3
#define PLATFORM_LINUX 5
#define PLATFORM_MAC 8

#define TARGET_PLATFORM PLATFORM_UNKNOWN

// Apple: Mac and iOS
#if defined(__APPLE__) && !defined(ANDROID)
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#undef TARGET_PLATFORM
#define TARGET_PLATFORM PLATFORM_IOS
#elif TARGET_OS_MAC
#undef TARGET_PLATFORM
#define TARGET_PLATFORM PLATFORM_MAC
#endif
#endif

// android
#if defined(ANDROID)
#undef TARGET_PLATFORM
#define TARGET_PLATFORM PLATFORM_ANDROID
#endif

// win32
#if defined(_WIN32) && defined(_WINDOWS)
#undef TARGET_PLATFORM
#define TARGET_PLATFORM PLATFORM_WIN32
#endif

// linux
#if defined(LINUX) && !defined(__APPLE__)
#undef TARGET_PLATFORM
#define TARGET_PLATFORM PLATFORM_LINUX
#endif

// check user set platform
#if !TARGET_PLATFORM
#error \
    "Cannot recognize the target platform; are you targeting an unsupported platform?"
#endif

#if (TARGET_PLATFORM == PLATFORM_WIN32)
#ifndef __MINGW32__
#pragma warning(disable : 4127)
#endif
#endif  // CC_PLATFORM_WIN32

#if ((TARGET_PLATFORM == PLATFORM_ANDROID) || (TARGET_PLATFORM == PLATFORM_IOS))
#define PLATFORM_MOBILE
#else
#define PLATFORM_PC
#endif

#if (TARGET_PLATFORM == PLATFORM_MAC) || (TARGET_PLATFORM == PLATFORM_IOS)
#define USE_GL
#elif (TARGET_PLATFORM == PLATFORM_ANDROID)
#define USE_GLES
#else
#define USE_GL
#endif
