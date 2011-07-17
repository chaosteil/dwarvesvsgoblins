#ifndef DVG_SRC_GAME_TILES_TILE_H_
#define DVG_SRC_GAME_TILES_TILE_H_

#include <stdint.h>
#include "utils/components/logic_component.h"

namespace dvg {
namespace game {

class Tile : public utils::LogicComponent {
 public:
  enum Flags {
    kFlag_None = 0,
    kFlag_Solid = 1,
    kFlag_Water = 2,
    kFlag_Lava = 4,
    kFlag_Diggable = 8,
    kFlag_Claimable = 16
  };

  Tile(uint8_t flags);
  virtual ~Tile();

  bool solid() const { return flags_ & kFlag_Solid; } 
  bool water() const { return flags_ & kFlag_Water; } 
  bool lava() const { return flags_ & kFlag_Lava; } 
  bool diggable() const { return flags_ & kFlag_Diggable; } 
  bool claimable() const { return flags_ & kFlag_Claimable; } 

  virtual void Dig() {}
  virtual void Claim() {}
  virtual void DoSpecial() {}

  // TODO(Chaosteil): Return claimed player

 private:
  uint8_t flags_;
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_TILES_TILE_H_
