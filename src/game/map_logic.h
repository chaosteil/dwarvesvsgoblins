#ifndef DVG_SRC_GAME_MAP_LOGIC_H_
#define DVG_SRC_GAME_MAP_LOGIC_H_

#include <boost/unordered_map.hpp>
#include <vector>

#include "utils/components/logic_component.h"
#include "utils/vector2d.h"

namespace dvg {
namespace utils { 
class GameObject; 
class SceneManager; 
}
namespace game {

class MapLogic : public utils::LogicComponent {
 public:   
  MapLogic(const utils::Vector2d &size, utils::SceneManager &scene_manager);
  virtual ~MapLogic();

  void Init(utils::GameObject &);
  void Update(utils::GameObject &);
  
  std::vector<utils::GameObject *> &tiles();
  utils::Vector2d size() const;

 private:
  std::vector<utils::GameObject *> tiles_;
  utils::Vector2d size_;
  
  utils::SceneManager &scene_manager_;
  
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_MAP_LOGIC_H_
