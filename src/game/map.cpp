#include "game/map.h"

#include <cstdlib>

namespace dvg {
namespace game {

Map::Map(int width, int height)
  : width_(width), height_(height), data_(new Tile*[width*height]) {

  // Generate random tiles [0, 1]
  int size = width_ * height_;
  for (int i = 0; i < size; i++) {
    data_[i] = new Tile(std::rand() % 2);
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
