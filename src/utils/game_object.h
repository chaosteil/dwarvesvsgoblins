#ifndef DVG_SRC_UTILS_GAME_OBJECT_H_
#define DVG_SRC_UTILS_GAME_OBJECT_H_

#include <list>

namespace dvg {
namespace utils {

class GameObject {
 public:
  GameObject() {}
  virtual ~GameObject() {}

  void AddComponent(GameComponent *component) {
    components_.push_back(component);
  }

 private:
  std::list<GameComponent*> components_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_GAME_OBJECT_H_
