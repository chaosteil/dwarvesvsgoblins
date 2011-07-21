#ifndef DVG_SRC_GAME_MAP_LOGIC_H_
#define DVG_SRC_GAME_MAP_LOGIC_H_

#include "utils/components/logic_component.h"
#include "utils/vector2d.h"

namespace dvg {
namespace utils { class GameObject; class SceneManager; }
namespace game {

class Map;

class MapLogic : public utils::LogicComponent {
 public:   
  MapLogic(const utils::Vector2d &size, utils::SceneManager &scene_manager);
  virtual ~MapLogic();

  void Init(utils::GameObject &);
  void Update(utils::GameObject &);

  Map &map() { return *map_; }
  
 private:
  Map *map_;
  
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_MAP_LOGIC_H_
