#ifndef DVG_SRC_UTILS_POSITION_COMPONENT_H_
#define DVG_SRC_UTILS_POSITION_COMPONENT_H_

#include "utils/game_component.h"
#include "utils/vector2d.h"

namespace dvg {
namespace utils {

class PositionComponent : public GameComponent {
 public:
  PositionComponent(GameObject &game_object,
                    GameComponentManager &manager,
                    const Vector2d &position,
                    const Vector2d &velocity,
                    double angle);
  virtual ~PositionComponent();

  const Vector2d &position() const { return position_; }
  const Vector2d &velocity() const { return velocity_; }
  double angle() const { return angle_; }

 private:
  Vector2d position_;
  Vector2d velocity_;
  double angle_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_POSITION_COMPONENT_H_
