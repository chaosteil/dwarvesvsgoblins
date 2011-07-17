#ifndef DVG_SRC_GAME_TILES_WALL_TILE_H_
#define DVG_SRC_GAME_TILES_WALL_TILE_H_

#include "game/tiles/tile.h"

namespace dvg {
namespace game {

class WallTile : public Tile {
 public:
  WallTile();
  virtual ~WallTile();

  virtual void Dig();
  virtual void Claim();

 private:
  int health_;
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_TILES_SOLID_TILE_H_
