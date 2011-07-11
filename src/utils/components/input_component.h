#ifndef DVG_SRC_UTILS_COMPONENTS_INPUT_COMPONENT_H_
#define DVG_SRC_UTILS_COMPONENTS_INPUT_COMPONENT_H_

#include <list>
#include <boost/foreach.hpp>

namespace dvg {
namespace utils {

class GameObject;

class InputComponent {
 public:
  virtual ~InputComponent() {}
  virtual void Init(GameObject &) {}

  virtual void HandleInput(GameObject &game_object) = 0;

 protected:
  InputComponent() {}
};

class EmptyInputComponent : public InputComponent {
 public:
  EmptyInputComponent() {}
  virtual ~EmptyInputComponent() {}

  virtual void HandleInput(GameObject &) {}
};

class CompositeInputComponent : public InputComponent {
 public:
  CompositeInputComponent() {}
  virtual ~CompositeInputComponent() {
    BOOST_FOREACH (InputComponent *component, components_) {
      delete component;
    }
  }

  virtual void AddComponent(InputComponent *component) {
    components_.push_back(component);
  }
  
  virtual void HandleInput(GameObject &game_object) {
    BOOST_FOREACH (InputComponent *component, components_) {
      component->HandleInput(game_object);
    }
  }

 private:
  std::list<InputComponent*> components_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_COMPONENTS_INPUT_COMPONENT_H_
