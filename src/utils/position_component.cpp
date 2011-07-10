#include "utils/position_component.h"

namespace dvg {
namespace utils {

PositionComponent::PositionComponent(GameObject &game_object,
                                     GameComponentManager &manager,
                                     const Vector2d &position,
                                     const Vector2d &velocity,
                                     double angle)
  : GameComponent(game_object, manager),
    position_(position), velocity_(velocity), angle_(angle) {}

PositionComponent::~PositionComponent() {}

}  // namespace utils
}  // namespace dv&
