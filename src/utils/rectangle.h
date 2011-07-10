#ifndef DVG_SRC_UTILS_RECTANGLE_H_
#define DVG_SRC_UTILS_RECTANGLE_H_

#include "utils/vector2d.h"

namespace dvg {
namespace utils {

class Rectangle {
 public:
  Rectangle(const Vector2d &pos, const Vector2d &size)
      : pos_(pos), size_(size) {}
  virtual ~Rectangle() {}

  const Vector2d &pos() const { return pos_; }
  const Vector2d &size() const { return size_; }

  void set_pos(const Vector2d &pos) { pos_ = pos; }
  void set_size(const Vector2d &size) { size_ = size; }

  bool DoesIntersect(const Rectangle &rectangle) const;
  bool IsPositionIn(const Vector2d &pos) const;

 private:
  Vector2d pos_;
  Vector2d size_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_RECTANGLE_H_
