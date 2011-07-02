#include "game/map.h"

namespace dvg {
namespace game {

Map::Map(int width, int height)
  : width_(width), height_(height), data_(new char[width*height]) {}

Map::~Map() {
  delete[] data_;
}

}  // namespace game
}  // namespace dvg
