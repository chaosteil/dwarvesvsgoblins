#include "game/tiles/wall_tile.h"

#include <iostream>

namespace dvg {
namespace game {

WallTile::WallTile(Map &map)
    : Tile(kFlag_Solid | kFlag_Diggable | kFlag_Claimable, map), health_(3) {}

WallTile::~WallTile() {}

void WallTile::Dig() {
  health_--;

  if (health_ <= 0) {
    std::cout << "Spawn ground here" << std::endl;
  }
}

void WallTile::Claim() {}

}  // namespace game
}  // namespace dvg
