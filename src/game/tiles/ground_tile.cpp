#include "game/tiles/ground_tile.h"

namespace dvg {
namespace game {

GroundTile::GroundTile(Map &map) : Tile(kFlag_Claimable, map) {}

GroundTile::~GroundTile() {}

void GroundTile::Claim() {}

}  // namespace game
}  // namespace dvg
