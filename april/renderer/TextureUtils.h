
#pragma once

// #include "CCPlatformMacros.h"
#include "renderer/Texture2D.h"

namespace april {

namespace backend {
namespace PixelFormatUtils {
typedef april::backend::PixelFormat PixelFormat;

/**convert functions*/

/**
Convert the format to the format param you specified, if the format is
PixelFormat::Automatic, it will detect it automatically and convert to the
closest format for you. It will return the converted format to you. if the
outData != data, you must delete it manually.
*/
PixelFormat convertDataToFormat(const unsigned char* data, size_t dataLen,
                                PixelFormat originFormat, PixelFormat format,
                                unsigned char** outData, size_t* outDataLen);

PixelFormat convertI8ToFormat(const unsigned char* data, size_t dataLen,
                              PixelFormat format, unsigned char** outData,
                              size_t* outDataLen);
PixelFormat convertAI88ToFormat(const unsigned char* data, size_t dataLen,
                                PixelFormat format, unsigned char** outData,
                                size_t* outDataLen);
PixelFormat convertRGB888ToFormat(const unsigned char* data, size_t dataLen,
                                  PixelFormat format, unsigned char** outData,
                                  size_t* outDataLen);
PixelFormat convertRGBA8888ToFormat(const unsigned char* data, size_t dataLen,
                                    PixelFormat format, unsigned char** outData,
                                    size_t* outDataLen);
PixelFormat convertRGB5A1ToFormat(const unsigned char* data, size_t dataLen,
                                  PixelFormat format, unsigned char** outData,
                                  size_t* outDataLen);
PixelFormat convertRGB565ToFormat(const unsigned char* data, size_t dataLen,
                                  PixelFormat format, unsigned char** outData,
                                  size_t* outDataLen);
PixelFormat convertA8ToFormat(const unsigned char* data, size_t dataLen,
                              PixelFormat format, unsigned char** outData,
                              size_t* outDataLen);
PixelFormat convertRGBA4444ToFormat(const unsigned char* data, size_t dataLen,
                                    PixelFormat format, unsigned char** outData,
                                    size_t* outDataLen);
PixelFormat convertBGRA8888ToFormat(const unsigned char* data, size_t dataLen,
                                    PixelFormat format, unsigned char** outData,
                                    size_t* outDataLen);

// I8 to XXX
void convertI8ToRGB888(const unsigned char* data, size_t dataLen,
                       unsigned char* outData);
void convertI8ToRGBA8888(const unsigned char* data, size_t dataLen,
                         unsigned char* outData);
void convertI8ToRGB565(const unsigned char* data, size_t dataLen,
                       unsigned char* outData);
void convertI8ToRGBA4444(const unsigned char* data, size_t dataLen,
                         unsigned char* outData);
void convertI8ToRGB5A1(const unsigned char* data, size_t dataLen,
                       unsigned char* outData);
void convertI8ToAI88(const unsigned char* data, size_t dataLen,
                     unsigned char* outData);

// AI88 to XXX
void convertAI88ToRGB888(const unsigned char* data, size_t dataLen,
                         unsigned char* outData);
void convertAI88ToRGBA8888(const unsigned char* data, size_t dataLen,
                           unsigned char* outData);
void convertAI88ToRGB565(const unsigned char* data, size_t dataLen,
                         unsigned char* outData);
void convertAI88ToRGBA4444(const unsigned char* data, size_t dataLen,
                           unsigned char* outData);
void convertAI88ToRGB5A1(const unsigned char* data, size_t dataLen,
                         unsigned char* outData);
void convertAI88ToA8(const unsigned char* data, size_t dataLen,
                     unsigned char* outData);
void convertAI88ToI8(const unsigned char* data, size_t dataLen,
                     unsigned char* outData);

// RGB888 to XXX
void convertRGB888ToRGBA8888(const unsigned char* data, size_t dataLen,
                             unsigned char* outData);
void convertRGB888ToRGB565(const unsigned char* data, size_t dataLen,
                           unsigned char* outData);
void convertRGB888ToA8(const unsigned char* data, size_t dataLen,
                       unsigned char* outData);
void convertRGB888ToI8(const unsigned char* data, size_t dataLen,
                       unsigned char* outData);
void convertRGB888ToAI88(const unsigned char* data, size_t dataLen,
                         unsigned char* outData);
void convertRGB888ToRGBA4444(const unsigned char* data, size_t dataLen,
                             unsigned char* outData);
void convertRGB888ToRGB5A1(const unsigned char* data, size_t dataLen,
                           unsigned char* outData);

// RGBA8888 to XXX
void convertRGBA8888ToRGB888(const unsigned char* data, size_t dataLen,
                             unsigned char* outData);
void convertRGBA8888ToRGB565(const unsigned char* data, size_t dataLen,
                             unsigned char* outData);
void convertRGBA8888ToI8(const unsigned char* data, size_t dataLen,
                         unsigned char* outData);
void convertRGBA8888ToA8(const unsigned char* data, size_t dataLen,
                         unsigned char* outData);
void convertRGBA8888ToAI88(const unsigned char* data, size_t dataLen,
                           unsigned char* outData);
void convertRGBA8888ToRGBA4444(const unsigned char* data, size_t dataLen,
                               unsigned char* outData);
void convertRGBA8888ToRGB5A1(const unsigned char* data, size_t dataLen,
                             unsigned char* outData);

void convertRGB5A1ToRGBA8888(const unsigned char* data, size_t dataLen,
                             unsigned char* outData);
void convertRGB565ToRGBA8888(const unsigned char* data, size_t dataLen,
                             unsigned char* outData);
void convertA8ToRGBA8888(const unsigned char* data, size_t dataLen,
                         unsigned char* outData);
void convertRGBA4444ToRGBA8888(const unsigned char* data, size_t dataLen,
                               unsigned char* outData);

// BGRA8888 to XXX
void convertBGRA8888ToRGBA8888(const unsigned char* data, size_t dataLen,
                               unsigned char* outData);
};  // namespace PixelFormatUtils
}  // namespace backend

}  // namespace april
