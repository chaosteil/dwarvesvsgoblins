#ifndef DVG_SRC_GAME_MAP_H_
#define DVG_SRC_GAME_MAP_H_

namespace dvg {
namespace game {

class Tile;

class Map {
 public:
  Map(int width, int height);
  virtual ~Map();

  int width() const { return width_; }
  int height() const { return height_; }
  const Tile &data(int x, int y) const { return *data_[x + y * width_]; }

 private:
  int width_;
  int height_;
  Tile **data_;
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_MAP_H_
