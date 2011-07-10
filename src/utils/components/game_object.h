#ifndef DVG_SRC_UTILS_COMPONENTS_GAME_OBJECT_H_
#define DVG_SRC_UTILS_COMPONENTS_GAME_OBJECT_H_

#include "utils/components/input_component.h"
#include "utils/components/logic_component.h"
#include "utils/components/render_component.h"
#include "utils/components/event_component.h"
#include "utils/rectangle.h"
#include "utils/vector2d.h"

namespace dvg {
namespace utils {

class InputComponent;
class LogicComponent;
class RenderComponent;
class EventComponent;

class GameObject {
 public:
  GameObject(InputComponent *input_component,
             LogicComponent *logic_component,
             RenderComponent *render_component,
             EventComponent *event_component,
             Rectangle position,
             Vector2d velocity,
             double angle);
  virtual ~GameObject();

  const Rectangle &position() const { return position_; }
  const Vector2d &velocity() const { return velocity_; }
  double angle() const { return angle_; }

  void HandleInput() {
    input_component_->HandleInput(*this);
  }

  void Update() {
    logic_component_->Update(*this);
  }

  void Render() {
    render_component_->Render(*this);
  }

 private:
  InputComponent *input_component_;
  LogicComponent *logic_component_;
  RenderComponent *render_component_;
  EventComponent *event_component_;

  Rectangle position_;
  Vector2d velocity_;

  double angle_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_COMPONENTS_GAME_OBJECT_H_
