#include "game/wall_tile.h"

#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace dvg {
namespace game {

WallTileLogic::WallTileLogic(char data) : health_(3), data_(data) {}

WallTileLogic::~WallTileLogic() {}

void WallTileLogic::Update(utils::GameObject &) {
  if (health_ <= 0) {
    
  }
}

WallTileInput::WallTileInput(WallTileLogic &logic) : logic_(logic) {}

WallTileInput::~WallTileInput() {}

void WallTileInput::HandleInput(utils::GameObject &, const sf::Event &event) {
  if (event.Key.Code == sf::Keyboard::Up) {
    logic_.set_data(1);
  }
}

}  // namespace game
}  // namespace dvg
