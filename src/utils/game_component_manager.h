#ifndef DVG_SRC_UTILS_GAME_COMPONENT_MANAGER_H_
#define DVG_SRC_UTILS_GAME_COMPONENT_MANAGER_H_

namespace dvg {
namespace utils {

class GameComponentManager {
 public:
  GameComponentManager() {}
  virtual ~GameComponentManager() {}

  bool HasComponent(Component *component) const = 0;
  void Cleanup(Component *component) = 0;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_GAME_COMPONENT_MANAGER_H_
