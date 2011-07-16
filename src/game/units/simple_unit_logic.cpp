#include "game/units/simple_unit_logic.h"

#include <cstdlib>
#include "utils/game_object.h"

namespace dvg {
namespace game {

SimpleUnitLogic::SimpleUnitLogic() : timer_(0) {}

SimpleUnitLogic::~SimpleUnitLogic() {}

void SimpleUnitLogic::Update(utils::GameObject &game_object) {
  timer_ += 0.1;
  if (timer_ >= 1.0) {
    utils::Vector2d pos = game_object.position().pos();

    double move = (std::rand() % 3 - 1);
    move /= 2;

    double direction = std::rand() % 2;
    double rotation = std::rand() % 30 - 15;

    utils::Vector2d delta(direction > 0 ? move : 0, direction > 0 ? 0 : move);

    game_object.set_pos(pos + delta);
    game_object.set_angle(game_object.angle() + rotation);

    timer_ = 0;
  }
}

}  // namespace game
}  // namespace dvg
