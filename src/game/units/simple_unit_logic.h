#ifndef DVG_SRC_GAME_UNITS_SIMPLE_UNIT_LOGIC_H_
#define DVG_SRC_GAME_UNITS_SIMPLE_UNIT_LOGIC_H_

#include "utils/components/logic_component.h"

namespace dvg {
namespace game {

class SimpleUnitLogic : public utils::LogicComponent {
 public:
  SimpleUnitLogic();
  virtual ~SimpleUnitLogic();

  virtual void Update(utils::GameObject &game_object);

 private:
  double timer_;
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_UNITS_SIMPLE_UNIT_LOGIC_H_
