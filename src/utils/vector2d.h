#ifndef DVG_SRC_UTILS_VECTOR2D_H_
#define DVG_SRC_UTILS_VECTOR2D_H_

#include <cmath>
#include <boost/functional/hash.hpp>

namespace dvg {
namespace utils {

class Vector2d {
 public:  
  friend std::size_t hash_value(const Vector2d &v){ 
    std::size_t hashed_value = 0;
    boost::hash_combine(hashed_value, (int)v.x());
    boost::hash_combine(hashed_value, (int)v.y());
    return hashed_value;
  } 
  
  explicit Vector2d(double x = 0, double y = 0) : x_(x), y_(y) {}
  Vector2d(const Vector2d &v) : x_(v.x_), y_(v.y_) {}
  virtual ~Vector2d() {}

  bool operator==(const Vector2d &v) const {
    return x_ == v.x_ && y_ == v.y_;
  }

  bool operator!=(const Vector2d &v) const {
    return !(*this == v);
  }

  const Vector2d operator+(const Vector2d &v) const {
    Vector2d result(x_ + v.x_, y_ + v.y_);

    return result;
  }

  const Vector2d operator-(const Vector2d &v) const {
    Vector2d result(x_ - v.x_, y_ - v.y_);

    return result;
  }

  const Vector2d operator*(double d) const {
    Vector2d result(x_ * d, y_ * d);

    return result;
  }

  double operator*(const Vector2d &v) const { return x_ * v.x_ + y_ * v.y_; }

  double length() const { return ::sqrt((*this) * (*this)); }
  
  const Vector2d Normalize() const {
    double l = length();
    if (l == 0) {
      return Vector2d(0, 0);
    }

    return Vector2d(x_/l, y_/l);
  }

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
