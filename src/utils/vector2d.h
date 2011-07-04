#ifndef DVG_SRC_UTILS_VECTOR2D_H_
#define DVG_SRC_UTILS_VECTOR2D_H_

#include <cmath>

namespace dvg {
namespace utils {

class Vector2d {
 public:
  explicit Vector2d(double x = 0, double y = 0) : x_(x), y_(y) {}
  Vector2d(const Vector2d &v) : x_(v.x_), y_(v.y_) {}
  virtual ~Vector2d() {}

  const Vector2d &operator+(const Vector2d &v) {
    x_ += v.x_;
    y_ += v.y_;

    return *this;
  }

  const Vector2d &operator-(const Vector2d &v) {
    x_ -= v.x_;
    y_ -= v.y_;

    return *this;
  }

  const Vector2d &operator*(double d) {
    x_ *= d;
    y_ *= d;

    return *this;
  }
  double operator*(const Vector2d &v) const { return x_ * v.x_ + y_ * v.y_; }

  double length() const { return ::sqrt((*this) * (*this)); }

  double x() const { return x_; }
  double y() const { return y_; }
  int xi() const { return (int)x_; }
  int yi() const { return (int)y_; }
  Vector2d &set_x(double x) { x_ = x; return *this; }
  Vector2d &set_y(double y) { y_ = y; return *this; }

 private:
  double x_;
  double y_;
};

}  // namespace utils 
}  // namespace dvg

#endif  // DVG_SRC_GAME_VECTOR2D_H_
