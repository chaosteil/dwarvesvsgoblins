#ifndef DVG_SRC_UTILS_GAME_COMPONENT_H_
#define DVG_SRC_UTILS_GAME_COMPONENT_H_

#include "utils/game_component_manager.h"

namespace dvg {
namespace utils {

class GameObject;

class GameComponent {
 public:
  GameComponent(GameObject &game_object,
                GameComponentManager &manager)
      : game_object_(game_object), manager_(manager) {}
  virtual ~GameComponent() { manager_.Cleanup(this); }

  // TODO: Receive Message
 
 protected:
  GameObject &game_object() const { return game_object_; }
 
 private:
  GameObject &game_object_;
  GameComponentManager &manager_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_GAME_COMPONENT_H_
