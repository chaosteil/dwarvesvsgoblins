#ifndef DVG_SRC_UTILS_GAME_OBJECT_H_
#define DVG_SRC_UTILS_GAME_OBJECT_H_

#include "utils/components/input_component.h"
#include "utils/components/logic_component.h"
#include "utils/components/render_component.h"
#include "utils/components/event_component.h"
#include "utils/rectangle.h"
#include "utils/vector2d.h"

namespace dvg {
namespace utils {

class GameObjectManager;

class GameObject {
 public:
  GameObject(GameObjectManager &manager,
             InputComponent *input_component,
             LogicComponent *logic_component,
             RenderComponent *render_component,
             EventComponent *event_component,
             Rectangle position,
             Vector2d velocity,
             double angle);
  virtual ~GameObject();

  void Destroy();

  bool active() const { return active_; }
  const Rectangle &position() const { return position_; }
  const Vector2d &velocity() const { return velocity_; }
  double angle() const { return angle_; }

  void set_position(const Rectangle &position) { position_ = position; }
  void set_pos(const Vector2d &position) { position_.set_pos(position); }
  void set_size(const Vector2d &size) { position_.set_size(size); }
  void set_velocity(const Vector2d &velocity) { velocity_ = velocity; }
  void set_angle(double angle) { angle_ = angle; }

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
  GameObjectManager &manager_;
  InputComponent *input_component_;
  LogicComponent *logic_component_;
  RenderComponent *render_component_;
  EventComponent *event_component_;

  Rectangle position_;
  Vector2d velocity_;

  double angle_;
  
  bool active_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_GAME_OBJECT_H_
