#ifndef DVG_SRC_UTILS_GAME_OBJECT_H_
#define DVG_SRC_UTILS_GAME_OBJECT_H_

#include <list>

namespace dvg {
namespace utils {

class GameComponent;

class GameObject {
 public:
  GameObject() {}
  virtual ~GameObject() {
    BOOST_FOREACH (GameComponent *component, components_) {
      delete component;
    }
  }

  void AddComponent(GameComponent *component) {
    components_.push_back(component);
  }

 private:
  std::list<GameComponent*> components_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_GAME_OBJECT_H_
