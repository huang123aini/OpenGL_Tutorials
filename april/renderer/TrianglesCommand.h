/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-24 13:19:42
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-24 13:42:15
 * @FilePath: /OpenGL_Tutorials/april/renderer/TrianglesCommand.h
 */

#pragma once

#include "renderer/PipelineDescriptor.h"
#include "renderer/RenderCommand.h"

namespace april {
/**
 Command used to render one or more Triangles, which is similar to QuadCommand.
 Every TrianglesCommand will have generate material ID by give textureID,
 glProgramState, Blend function if the material id is the same, these
 TrianglesCommands could be batched to save draw call.
*/
namespace backend {
class TextureBackend;
class Program;
}  // namespace backend

class Texture2D;

class TrianglesCommand : public RenderCommand {
 public:
  struct Triangles {
    Triangles(V3F_C4B_T2F* _verts, unsigned short* _indices,
              unsigned int _vertCount, unsigned int _indexCount)
        : verts(_verts),
          indices(_indices),
          vertCount(_vertCount),
          indexCount(_indexCount) {}

    Triangles() {}

    V3F_C4B_T2F* verts = nullptr;
    unsigned short* indices = nullptr;
    unsigned int vertCount = 0;
    unsigned int indexCount = 0;
  };

  TrianglesCommand();
  ~TrianglesCommand();

  /** Initializes the command.
   @param globalOrder GlobalZOrder of the command.
   @param texture The texture used in renderring.
   @param blendType Blend function for the command.
   @param triangles Rendered triangles for the command.
   @param mv ModelView matrix for the command.
   @param flags to indicate that the command is using 3D rendering or not.
   */
  void init(float globalOrder, april::Texture2D* texture,
            const BlendFunc& blendType, const Triangles& triangles,
            const glm::mat4& mv, uint32_t flags);

  /**Get the material id of command.*/
  uint32_t getMaterialID() const { return _materialID; }

  const Triangles& getTriangles() const { return _triangles; }

  size_t getVertexCount() const { return _triangles.vertCount; }

  size_t getIndexCount() const { return _triangles.indexCount; }

  const V3F_C4B_T2F* getVertices() const { return _triangles.verts; }

  const unsigned short* getIndices() const { return _triangles.indices; }

  const glm::mat4& getModelView() const { return _mv; }

  void updateMaterialID();

 protected:
  /**Generate the material ID by textureID, glProgramState, and blend
   * function.*/
  void generateMaterialID();

  uint32_t _materialID = 0;

  Triangles _triangles;

  /**Model view matrix when rendering the triangles.*/
  glm::mat4 _mv;

  uint8_t _alphaTextureID = 0;  // ANDROID ETC1 ALPHA supports.

  // Cached value to determine to generate material id or not.
  BlendFunc _blendType = BlendFunc::DISABLE;
  backend::ProgramType _programType = backend::ProgramType::CUSTOM_PROGRAM;
  backend::TextureBackend* _texture = nullptr;
};

}  // namespace april