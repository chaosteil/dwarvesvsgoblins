#include "game/wall_tile.h"

#include <iostream>

namespace dvg {
namespace game {

WallTileLogic::WallTileLogic(char data) : data_(data) {}

WallTileLogic::~WallTileLogic() {}

void WallTileLogic::Update(utils::GameObject &) {}

WallTileInput::WallTileInput(WallTileLogic &logic) : logic_(logic) {}

WallTileInput::~WallTileInput() {}

void WallTileInput::HandleInputEvent(utils::GameObject &, const sf::Event &) {}

void WallTileInput::HandleInput(utils::GameObject &,
                                const sf::Input &input) {
  if (input.IsKeyDown(sf::Key::Up)) {
    logic_.set_data(1);
  }
}

}  // namespace game
}  // namespace dvg
