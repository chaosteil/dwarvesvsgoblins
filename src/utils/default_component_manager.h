#ifndef DVG_SRC_UTILS_DEFAULT_COMPONENT_MANAGER_H_
#define DVG_SRC_UTILS_DEFAULT_COMPONENT_MANAGER_H_

#include <boost/bimap.hpp>

#include "utils/game_object.h"
#include "utils/game_component_manager.h"

namespace dvg {
namespace utils {

class DefaultComponentManager : public GameComponentManager {
 public:
  DefaultComponentManager() {}
  virtual ~DefaultComponentManager() {}

  virtual bool HasComponent(GameComponent *component) const {
    return game_objects_.right.find(component) != game_objects_.right.end();
  }

  virtual void Cleanup(GameComponent *component) {
    game_objects_.right.erase(component);
  }

 private:
  boost::bimap<GameObject*, GameComponent*> game_objects_;
};
}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_DEFAULT_COMPONENT_MANAGER_H_
