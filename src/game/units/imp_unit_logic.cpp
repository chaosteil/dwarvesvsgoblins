#include "game/units/imp_unit_logic.h"

#include "utils/game_object.h"

namespace dvg {
namespace game {

ImpUnitLogic::ImpUnitLogic() {}

ImpUnitLogic::~ImpUnitLogic() {}

void ImpUnitLogic::Update(utils::GameObject &game_object) {
  utils::Vector2d pos = game_object.position().pos();
  utils::Vector2d velocity = (target_ - pos).Normalize() * 0.001;

  game_object.set_pos(pos + velocity);
  game_object.set_velocity(velocity);
}

ImpUnitInput::ImpUnitInput(ImpUnitLogic &logic) : logic_(logic) {}

ImpUnitInput::~ImpUnitInput() {}

void ImpUnitInput::HandleInputEvent(utils::GameObject &, const sf::Event &) {}

void ImpUnitInput::HandleInput(utils::GameObject &, const sf::Input &input) {
  utils::Vector2d target;
  target.set_x(input.GetMouseX()/64.0);
  target.set_y(input.GetMouseY()/64.0);

  logic_.SetTargetTile(target);
}

}  // namespace game
}  // namespace dvg
