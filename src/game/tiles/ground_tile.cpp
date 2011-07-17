#include "game/tiles/ground_tile.h"

namespace dvg {
namespace game {

GroundTile::GroundTile() : Tile(kFlag_Claimable) {}

GroundTile::~GroundTile() {}

void GroundTile::Claim() {}

}  // namespace game
}  // namespace dvg
