#ifndef DVG_SRC_UTILS_SCENE_MANAGER_H_
#define DVG_SRC_UTILS_SCENE_MANAGER_H_

#include <vector>

#include "utils/game_object_manager.h"

namespace dvg {
namespace utils {

class GameObject;
  
class SceneManager : public GameObjectManager {
 public:
  SceneManager();
  virtual ~SceneManager();

  virtual void NotifyDestroyed(GameObject &) {}

  void Attach(GameObject *object);
  void Update();
  void Render();
  void HandleInput();
 
 private:
  std::vector<GameObject *> objects_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_SCENE_MANAGER_H_
