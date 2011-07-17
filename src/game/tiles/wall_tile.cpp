#include "game/tiles/wall_tile.h"

namespace dvg {
namespace game {

WallTile::WallTile()
    : Tile(kFlag_Solid | kFlag_Diggable | kFlag_Claimable), health_(3) {}

WallTile::~WallTile() {}

void WallTile::Dig() {
  health_--;
}

void WallTile::Claim() {}

}  // namespace game
}  // namespace dvg
