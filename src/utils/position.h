#ifndef DVG_SRC_GAME_POSITION_H_
#define DVG_SRC_GAME_POSITION_H_

namespace dvg {
namespace game {

class Position {
 public:
  explicit Position(double x = 0, double y = 0) : x_(x), y_(y) {}
  Position(const Position &p) : x_(p.x_), y_(p.y_) {}
  virtual ~Position() {}

  double x() const { return x_; }
  double y() const { return y_; }
  Position &set_x(double x) { x_ = x; return *this; }
  Position &set_y(double y) { y_ = y; return *this; }

 private:
  double x_;
  double y_;
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_POSITION_H_
