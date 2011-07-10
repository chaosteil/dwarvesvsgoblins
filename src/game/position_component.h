#ifndef DVG_SRC_GAME_POSITION_COMPONENT_H_
#define DVG_SRC_GAME_POSITION_COMPONENT_H_

#include "utils/game_component.h"
#include "utils/vector2d.h"

namespace dvg {
namespace game {

class PositionComponent : public utils::GameComponent {
 public:
  PositionComponent(utils::GameObject &game_object,
                    utils::GameComponentManager &manager,
                    const utils::Vector2d &position,
                    const utils::Vector2d &velocity,
                    double angle);
  virtual ~PositionComponent();

  const utils::Vector2d &position() const { return position_; }
  const utils::Vector2d &velocity() const { return velocity_; }
  double angle() const { return angle_; }

 private:
  utils::Vector2d position_;
  utils::Vector2d velocity_;
  double angle_;
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_POSITION_COMPONENT_H_
