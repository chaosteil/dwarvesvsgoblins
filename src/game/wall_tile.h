#ifndef DVG_SRC_GAME_WALL_TILE_H_
#define DVG_SRC_GAME_WALL_TILE_H_

#include "utils/components/input_component.h"
#include "utils/components/logic_component.h"

namespace sf { class Event; }

namespace dvg {
namespace game {

class WallTileLogic : public utils::LogicComponent {
 public:
  explicit WallTileLogic(char data);
  virtual ~WallTileLogic();

  int health() const { return health_; }
  void set_data(char data) { data_ = data; }
  char data() const { return data_; }

  void Damage(int damage) { health_ -= damage; }
  
  virtual void Update(utils::GameObject &game_object);
 
 private:
  int health_;
  char data_;
};

class WallTileInput : public utils::InputComponent {
 public:
  explicit WallTileInput(WallTileLogic &logic);
  virtual ~WallTileInput();

  virtual void HandleInput(utils::GameObject &game_object,
                                const sf::Event &event);

 private:
  WallTileLogic &logic_;
};


}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_WALL_TILE_H_
