#include "game/tiles/tile.h"

namespace dvg {
namespace game {

Tile::Tile(uint8_t flags, Map &map) : map_(map), flags_(flags) {}

Tile::~Tile() {}

}  // namespace game
}  // namespace dvg
