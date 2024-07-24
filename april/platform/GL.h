/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 15:12:26
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 15:34:27
 * @FilePath: /OpenGL_Tutorials/april/platform/APRIL_GL.h
 */

#pragma once

#include "platform/PlatformConfig.h"

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include "platform/android/GL-android.h"
#elif TARGET_PLATFORM == PLATFORM_WIN32
#include "platform/win32/GL-win32.h"
#elif TARGET_PLATFORM == PLATFORM_LINUX
#include "platform/linux/GL-linux.h"
#elif TARGET_PLATFORM == PLATFORM_MAC
#include "platform/Mac/GL-Mac.h"
#endif
