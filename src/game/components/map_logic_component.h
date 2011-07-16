#ifndef DVG_SRC_GAME_MAP_LOGIC_COMPONENT_H_
#define DVG_SRC_GAME_MAP_LOGIC_COMPONENT_H_

#include <boost/unordered_map.hpp>

#include "utils/components/logic_component.h"
#include "utils/vector2d.h"

namespace dvg {
namespace utils { 
class GameObject; 
class SceneManager; 
}
namespace game {

class MapLogicComponent : public utils::LogicComponent {
 public:
  typedef boost::unordered_map<utils::Vector2d, utils::GameObject *> ObjectMap;
   
  MapLogicComponent(const utils::Vector2d &size, utils::SceneManager &scene_manager);
  virtual ~MapLogicComponent();

  void Init(utils::GameObject &);
  void Update(utils::GameObject &);
  
  ObjectMap tiles();
  utils::Vector2d size() const;

 private:
  ObjectMap tiles_;
  utils::Vector2d size_;
  
  utils::SceneManager &scene_manager_;
  
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_MAP_LOGIC_COMPONENT_H_