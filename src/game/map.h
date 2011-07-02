#ifndef DVG_SRC_GAME_MAP_H_
#define DVG_SRC_GAME_MAP_H_

#include "game/tile.h"

namespace dvg {
namespace game {

class Map {
 public:
  Map(int width, int height);
  virtual ~Map();

  int width() const { return width_; }
  int height() const { return height_; }

  void set_data(int x, int y, char data) {
    data_[TranslateTile(x, y)]->set_data(data);
  }
  const Tile &data(int x, int y) const { return *data_[TranslateTile(x, y)]; }

 private:
  int TranslateTile(int x, int y) const { return x + y * width_; }

  int width_;
  int height_;
  Tile **data_;
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_MAP_H_
