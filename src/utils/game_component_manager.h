#ifndef DVG_SRC_UTILS_GAME_COMPONENT_MANAGER_H_
#define DVG_SRC_UTILS_GAME_COMPONENT_MANAGER_H_

namespace dvg {
namespace utils {

template<class Component>
class GameComponentManager {
 public:
  GameComponentManager() {}
  virtual ~GameComponentManager() {}

  bool HasComponent(Component *component) const;

 protected:
  void AddComponent(Component *component);
  void RemoveComponent(Component *component);

 private:
  boost::unordered_map<Component*, Component*> components_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_GAME_COMPONENT_MANAGER_H_
