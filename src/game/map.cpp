#include "game/map.h"

#include <cstdlib>

namespace dvg {
namespace game {

Map::Map(const utils::Vector2d &s)
  : size_(s), null_(0), data_(new Tile*[size_.xi() * size_.yi()]) {

  // Generate random tiles [1, 2]
  int size = size_.x() * size_.y();
  for (int i = 0; i < size; i++) {
    data_[i] = new Tile(std::rand() % 2 + 1);
  }
}

Map::~Map() {
  int size = size_.x() * size_.y();
  for (int i = 0; i < size; i++) {
    delete data_[i];
  }
  delete[] data_;
}

}  // namespace game
}  // namespace dvg
