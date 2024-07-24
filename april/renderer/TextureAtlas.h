
#pragma once

#include <string>

#include "base/Ref.h"
#include "base/aprilTypes.h"
// #include "base/ccConfig.h"

namespace april {

class Texture2D;
class EventCustom;
class EventListenerCustom;

/**
 * @addtogroup _2d
 * @{
 */

/** @brief A class that implements a Texture Atlas.
Supported features:
* The atlas file can be a PVRTC, PNG or any other format supported by Texture2D
* Quads can be updated in runtime
* Quads can be added in runtime
* Quads can be removed in runtime
* Quads can be re-ordered in runtime
* The TextureAtlas capacity can be increased or decreased in runtime
* OpenGL component: V3F, C4B, T2F.
The quads are rendered using an OpenGL ES VBO.
To render the quads using an interleaved vertex array list, you should modify
the ccConfig.h file

@warning If you want to use TextureAtlas, you'd better setup GL status before
it's rendered. Otherwise, the effect of TextureAtlas will be affected by the GL
status of other nodes.
*/
class TextureAtlas : public Ref {
 public:
  static TextureAtlas* create(const std::string& file, ssize_t capacity);

  static TextureAtlas* createWithTexture(Texture2D* texture, ssize_t capacity);

  TextureAtlas();

  virtual ~TextureAtlas();

  bool initWithFile(const std::string& file, ssize_t capacity);

  initWithTexture(Texture2D* texture, ssize_t capacity);

  void updateQuad(V3F_C4B_T2F_Quad* quad, ssize_t index);

  void insertQuad(V3F_C4B_T2F_Quad* quad, ssize_t index);

  void insertQuads(V3F_C4B_T2F_Quad* quads, ssize_t index, ssize_t amount);

  /** Removes the quad that is located at a certain index and inserts it at a
  new index. This operation is faster than removing and inserting in a quad in 2
  different steps.
   @since v0.7.2
  */
  void insertQuadFromIndex(ssize_t fromIndex, ssize_t newIndex);

  /** Removes a quad at a given index number.
  The capacity remains the same, but the total number of quads to be drawn is
  reduced in 1.
  @since v0.7.2
  */
  void removeQuadAtIndex(ssize_t index);

  /** Removes a amount of quads starting from index.
      @since 1.1
   */
  void removeQuadsAtIndex(ssize_t index, ssize_t amount);
  /** Removes all Quads.
  The TextureAtlas capacity remains untouched. No memory is freed.
  The total number of quads to be drawn will be 0.
  @since v0.7.2
  */
  void removeAllQuads();

  /** Resize the capacity of the TextureAtlas.
  * The new capacity can be lower or higher than the current one.
  * It returns true if the resize was successful.
  * If it fails to resize the capacity it will return false with a new capacity
  of 0.

   @param capacity Capacity for Quads.
  */
  bool resizeCapacity(ssize_t capacity);

  /**
   Used internally by ParticleBatchNode.
   don't use this unless you know what you're doing.
   @since 1.1
  */
  void increaseTotalQuadsWith(ssize_t amount);

  /** Moves an amount of quads from oldIndex at newIndex.
   @since v1.1
   */
  void moveQuadsFromIndex(ssize_t oldIndex, ssize_t amount, ssize_t newIndex);

  /**
   Moves quads from index till totalQuads to the newIndex.
   Used internally by ParticleBatchNode.
   This method doesn't enlarge the array if newIndex + quads to be moved >
   capacity.
   @since 1.1
  */
  void moveQuadsFromIndex(ssize_t index, ssize_t newIndex);

  /**
   Ensures that after a realloc quads are still empty.
   Used internally by ParticleBatchNode.
   @since 1.1
  */
  void fillWithEmptyQuadsFromIndex(ssize_t index, ssize_t amount);

  /** Whether or not the array buffer of the VBO needs to be updated.*/
  bool isDirty() { return _dirty; }
  /** Specify if the array buffer of the VBO needs to be updated. */
  void setDirty(bool bDirty) { _dirty = bDirty; }

  /**Get quads total amount.
   * @js NA
   * @lua NA
   */
  virtual std::string getDescription() const;

  /** Gets the quantity of quads that are going to be drawn. */
  size_t getTotalQuads() const;

  /** Gets the quantity of quads that can be stored with the current texture
   * atlas size. */
  size_t getCapacity() const;

  /** Gets the texture of the texture atlas. */
  Texture2D* getTexture() const;

  /** Sets the texture for the texture atlas. */
  void setTexture(Texture2D* texture);

  /** Gets the quads that are going to be rendered. */
  V3F_C4B_T2F_Quad* getQuads();

  /** Sets the quads that are going to be rendered. */
  void setQuads(V3F_C4B_T2F_Quad* quads);

  inline unsigned short* getIndices() { return _indices; }

 private:
  friend class ParticleBatchNode;
  friend class AtlasNode;

  void renderCommand();

  void setupIndices();

 protected:
  unsigned short* _indices = nullptr;
  bool _dirty = false;  // indicates whether or not the array buffer of the VBO
                        // needs to be updated
  /** quantity of quads that are going to be drawn */
  size_t _totalQuads = 0;
  /** quantity of quads that can be stored with the current texture atlas size
   */
  size_t _capacity = 0;
  /** Texture of the texture atlas */
  Texture2D* _texture = nullptr;
  /** Quads that are going to be rendered */
  V3F_C4B_T2F_Quad* _quads = nullptr;
};

}  // namespace april
