#ifndef DVG_SRC_GAME_TILES_GROUND_TILE_H_
#define DVG_SRC_GAME_TILES_GROUND_TILE_H_

#include "game/tiles/tile.h"

namespace dvg {
namespace game {

class GroundTile : public Tile {
 public:
  GroundTile();
  virtual ~GroundTile();

  virtual void Claim();
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_TILES_GROUND_TILE_H_
