/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-24 10:28:00
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-24 13:17:58
 * @FilePath: /OpenGL_Tutorials/april/renderer/RenderCommand.cpp
 */

// #include "2d/CCCamera.h"
// #include "2d/CCNode.h"

#include "renderer/RenderCommand.h"

namespace april {

RenderCommand::RenderCommand() {}

RenderCommand::~RenderCommand() {}

void RenderCommand::init(float globalZOrder, const glm::mat4 &transform,
                         unsigned int flags) {
  _globalOrder = globalZOrder;

  // TODO:huangshiping 暂时还没有设置相机
  if (/*flags & Node::FLAGS_RENDER_AS_3D*/ 0) {
    //     if (Camera::getVisitingCamera())
    //       _depth = Camera::getVisitingCamera()->getDepthInView(transform);

    set3D(true);
  } else {
    set3D(false);
    _depth = 0;
  }
}

void RenderCommand::printID() { printf("Command Depth: %f\n", _globalOrder); }

}  // namespace april
