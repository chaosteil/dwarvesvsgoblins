#ifndef DVG_SRC_UTILS_COMPONENTS_INPUT_COMPONENT_H_
#define DVG_SRC_UTILS_COMPONENTS_INPUT_COMPONENT_H_

#include <list>
#include <boost/foreach.hpp>
#include <SFML/Window/Event.hpp>

#include "utils/components/component.h"

namespace dvg {
namespace utils {

class GameObject;
class Message;

class InputComponent : public Component {
 public:
  virtual ~InputComponent() {}

  virtual void HandleInput(GameObject &game_object,
                           const sf::Event &event) = 0;

 protected:
  InputComponent() {}
};

class EmptyInputComponent : public InputComponent {
 public:
  EmptyInputComponent() {}
  virtual ~EmptyInputComponent() {}

  virtual void HandleInput(GameObject &, const sf::Event &) {}
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

  virtual void HandleInput(GameObject &game_object,
                                const sf::Event &event) {
    BOOST_FOREACH (InputComponent *component, components_) {
      component->HandleInput(game_object, event);
    }
  }

  void SendMessage(GameObject &obj, const Message &msg) {
    BOOST_FOREACH (InputComponent *component, components_) {
      component->SendMessage(obj, msg);
    }
  }

 private:
  std::list<InputComponent*> components_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_COMPONENTS_INPUT_COMPONENT_H_
