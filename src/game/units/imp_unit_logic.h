#ifndef DVG_SRC_GAME_UNITS_IMP_UNIT_LOGIC_H_
#define DVG_SRC_GAME_UNITS_IMP_UNIT_LOGIC_H_

#include "utils/components/input_component.h"
#include "utils/components/logic_component.h"
#include "utils/vector2d.h"

namespace dvg {

namespace utils { class GameObject; }

namespace game {

class ImpUnitLogic : public utils::LogicComponent {
 public:
  ImpUnitLogic();
  virtual ~ImpUnitLogic();

  virtual void Update(utils::GameObject &game_object);

  void SetTargetTile(utils::Vector2d position) { target_ = position; }
  
 private:
  utils::Vector2d target_;
};

class ImpUnitInput : public utils::InputComponent {
 public:
  explicit ImpUnitInput(ImpUnitLogic &logic);
  virtual ~ImpUnitInput();

  virtual void HandleInput(utils::GameObject &game_object,
                           const sf::Event &event);

 private:
  ImpUnitLogic &logic_;
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_UNITS_IMP_UNIT_LOGIC_H_
