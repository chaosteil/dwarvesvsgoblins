#include "game/map.h"

#include <cstdlib>
#include "game/tile.h"

namespace dvg {
namespace game {

Map::Map(int width, int height)
  : width_(width), height_(height), data_(new Tile*[width*height]) {

  // Generate random tiles [0, 1]
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      data_[x + y * width_] = new Tile(std::rand() % 2);
    }
  }
}

Map::~Map() {
  int size = width_ * height_;
  for (int i = 0; i < size; i++) {
    delete data_[i];
  }
  delete[] data_;
}

}  // namespace game
}  // namespace dvg
