#ifndef DVG_SRC_UTILS_GAME_COMPONENT_MANAGER_H_
#define DVG_SRC_UTILS_GAME_COMPONENT_MANAGER_H_

namespace dvg {
namespace utils {

class GameComponent;

class GameComponentManager {
 public:
  virtual ~GameComponentManager() {}

  virtual bool HasComponent(GameComponent *component) const = 0;
  virtual void Cleanup(GameComponent *component) = 0;

 protected:
  GameComponentManager() {}
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_GAME_COMPONENT_MANAGER_H_
