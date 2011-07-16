#ifndef DVG_SRC_GAME_WALL_TILE_H_
#define DVG_SRC_GAME_WALL_TILE_H_

#include "utils/components/input_component.h"
#include "utils/components/logic_component.h"

namespace dvg {
namespace game {

class WallTileLogic : public utils::LogicComponent {
 public:
  explicit WallTileLogic(char data);
  virtual ~WallTileLogic();

  void set_data(char data) { data_ = data; }
  char data() const { return data_; }
  
  virtual void Update(utils::GameObject &game_object);
 
 private:
  char data_;
};

class WallTileInput : public utils::InputComponent {
 public:
  explicit WallTileInput(WallTileLogic &logic);
  virtual ~WallTileInput();

  virtual void HandleInput(utils::GameObject &game_object,
                           const sf::Input &input);

 private:
  WallTileLogic &logic_;
};


}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_WALL_TILE_H_
