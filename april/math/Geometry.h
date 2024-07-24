#pragma once

#include <glm/vec2.hpp>

#include "base/BaseMacros.h"

/**
 * @addtogroup base
 * @{
 */

namespace april {

class Size {
 public:
  float width;
  float height;

 public:
  /**Conversion from Vec2 to Size.*/
  operator glm::vec2() const { return glm::vec2(width, height); }

 public:
  /**
  @{
  Constructor.
  @param width Width of the size.
  @param height Height of the size.
  @param other Copy constructor.
  @param point Conversion from a point.
   */
  Size();
  Size(float width, float height);
  Size(const Size& other);
  explicit Size(const glm::vec2& point);

  Size& operator=(const Size& other);

  Size& operator=(const glm::vec2& point);

  Size operator+(const Size& right) const;

  Size operator-(const Size& right) const;

  Size operator*(float a) const;

  Size operator/(float a) const;

  void setSize(float width, float height);

  bool equals(const Size& target) const;
  static const Size ZERO;
};

class Rect {
 public:
  glm::vec2 origin;
  Size size;

 public:
  Rect();

  Rect(float x, float y, float width, float height);

  Rect(const glm::vec2& pos, const Size& dimension);

  Rect(const Rect& other);

  Rect& operator=(const Rect& other);

  void setRect(float x, float y, float width, float height);

  float getMinX() const;

  float getMidX() const;

  float getMaxX() const;

  float getMinY() const;

  float getMidY() const;  /// return the midpoint y-value of current rect

  float getMaxY() const;  /// return the topmost y-value of current rect

  // bool equals(const Rect& rect) const;

  bool containsPoint(const glm::vec2& point) const;
  /**
  Check the intersect status of two rects.
   * @js NA
   */
  bool intersectsRect(const Rect& rect) const;
  /**
  Check the intersect status of the rect and a circle.
   * @js NA
   */
  bool intersectsCircle(const glm::vec2& center, float radius) const;
  /**
  Get the min rect which can contain this and rect.
   * @js NA
   * @lua NA
   */
  Rect unionWithRect(const Rect& rect) const;
  /**Compute the min rect which can contain this and rect, assign it to this.*/
  void merge(const Rect& rect);
  /**An empty Rect.*/
  static const Rect ZERO;
};

}  // namespace april