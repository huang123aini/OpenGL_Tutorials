/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 13:07:26
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 13:28:03
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/CommandBuffer.cpp
 */

#include "CommandBuffer.h"

namespace april {
namespace backend {

void CommandBuffer::setStencilReferenceValue(uint32_t value) {
  _stencilReferenceValueBack = _stencilReferenceValueFront = value;
}

void CommandBuffer::setStencilReferenceValue(unsigned int frontRef,
                                             unsigned int backRef) {
  _stencilReferenceValueFront = frontRef;
  _stencilReferenceValueBack = backRef;
}

}  // namespace backend
}  // namespace april
