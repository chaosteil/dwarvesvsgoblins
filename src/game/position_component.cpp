#include "game/position_component.h"

namespace dvg {
namespace game {

PositionComponent::PositionComponent(utils::GameObject &game_object,
                                     utils::GameComponentManager &manager,
                                     const utils::Vector2d &position,
                                     const utils::Vector2d &velocity,
                                     double angle)
  : GameComponent(game_object, manager),
    position_(position), velocity_(velocity), angle_(angle) {}

PositionComponent::~PositionComponent() {}

}  // namespace game
}  // namespace dv&
