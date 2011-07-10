#include "utils/components/game_object.h"

namespace dvg {
namespace utils {

GameObject::GameObject(InputComponent *input_component,
                       LogicComponent *logic_component,
                       RenderComponent *render_component,
                       EventComponent *event_component,
                       Rectangle position,
                       Vector2d velocity,
                       double angle)
    : input_component_(input_component), logic_component_(logic_component),
      render_component_(render_component), event_component_(event_component),
      position_(position), velocity_(velocity), angle_(angle) {}

GameObject::~GameObject() {
  delete event_component_;
  delete render_component_;
  delete logic_component_;
  delete input_component_;
}

}  // namespace utils
}  // namespace dvg
