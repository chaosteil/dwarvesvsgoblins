#ifndef DVG_SRC_UTILS_GAME_OBJECT_MANAGER_H_
#define DVG_SRC_UTILS_GAME_OBJECT_MANAGER_H_

namespace dvg {
namespace utils {

class GameObject;

class GameObjectManager {
 public:
  virtual ~GameObjectManager() {}
  
  virtual void NotifyDestroyed(GameObject &object) = 0;

 protected:
  GameObjectManager() {}
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_GAME_OBJECT_MANAGER_H_
