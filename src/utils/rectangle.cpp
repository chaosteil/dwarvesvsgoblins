#include "utils/rectangle.h"

namespace dvg {
namespace utils {

bool Rectangle::DoesIntersect(const Rectangle &rect) const {
  Vector2d bottomright = rect.pos()+rect.size();
  Vector2d r_bottomright = pos_+size_;

  if (pos_.x() < bottomright.x() && r_bottomright.x() > rect.pos().x() &&
      pos_.y() < bottomright.y() && r_bottomright.y() > rect.pos().y()) {
    return true;
  } else {
    return false;
  }
}

bool Rectangle::IsPositionIn(const Vector2d &pos) const {
  Vector2d bottomright = pos_+size_;

  if (pos_.x() <= pos.x() && pos_.y() <= pos.y() &&
      bottomright.x() >= pos.x() && bottomright.y() >= pos.y()) {
    return true;
  } else {
    return false;
  }
}

}  // namespace utils
}  // namespace dvg
