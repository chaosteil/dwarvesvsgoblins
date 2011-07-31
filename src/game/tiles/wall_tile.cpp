#include "game/tiles/wall_tile.h"

#include "game/map.h"
#include "game/tiles/ground_tile.h"

#include <iostream>

namespace dvg {
namespace game {

WallTile::WallTile(Map &map)
    : Tile(kFlag_Solid | kFlag_Diggable | kFlag_Claimable, map), health_(3),
      game_object_(NULL) {}

WallTile::~WallTile() {}

void WallTile::Init(utils::GameObject &game_object) {
  game_object_ = &game_object;
}

void WallTile::Dig() {
  health_--;

  if (health_ <= 0) {
    map().ReplaceTile(game_object_->position().pos(), new GroundTile(map()));
  }
}

void WallTile::Claim() {}

}  // namespace game
}  // namespace dvg
