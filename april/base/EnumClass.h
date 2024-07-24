/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-24 10:49:46
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-24 10:49:57
 * @FilePath: /OpenGL_Tutorials/april/base/EnumClass.h
 */
#pragma once

#include <type_traits>

namespace april {

template <typename Enum>
struct EnableBitMaskOperators {
  static const bool enable = false;
};

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator|(Enum lhs, Enum rhs) {
  using underlying = typename std::underlying_type<Enum>::type;
  return static_cast<Enum>(static_cast<underlying>(lhs) |
                           static_cast<underlying>(rhs));
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, bool>::type
operator==(Enum lhs, Enum rhs) {
  using underlying = typename std::underlying_type<Enum>::type;
  static_cast<underlying>(lhs) == static_cast<underlying>(rhs);
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
operator|=(Enum& lhs, Enum rhs) {
  using underlying = typename std::underlying_type<Enum>::type;
  lhs = static_cast<Enum>(static_cast<underlying>(lhs) |
                          static_cast<underlying>(rhs));

  return lhs;
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable,
                        unsigned int>::type
operator&(Enum lhs, Enum rhs) {
  using underlying = typename std::underlying_type<Enum>::type;
  using impl_type = typename std::make_unsigned<underlying>::type;
  return impl_type(static_cast<impl_type>(lhs) & static_cast<impl_type>(rhs));
}

#define ENABLE_BITMASK_OPERATORS(x)  \
  template <>                        \
  struct EnableBitMaskOperators<x> { \
    static const bool enable = true; \
  };

}  // namespace april
