#ifndef DVG_SRC_UTILS_COMPONENTS_RENDER_COMPONENT_H_
#define DVG_SRC_UTILS_COMPONENTS_RENDER_COMPONENT_H_

#include <list>
#include <boost/foreach.hpp>

#include "utils/components/component.h"

namespace sf { class RenderWindow; }

namespace dvg {
namespace utils {

class GameObject;
class Message;

class RenderComponent : public Component {
 public:
  virtual ~RenderComponent() {}

  virtual void Render(GameObject &game_object, sf::RenderWindow &window) = 0;
  
  double standard_scale() { return 4.0f; }
  double base_size() { return 4.0f * 16.0f; }

 protected:
  RenderComponent() {}
};

class EmptyRenderComponent : public RenderComponent {
 public:
  EmptyRenderComponent() {}
  virtual ~EmptyRenderComponent() {}

  virtual void Render(GameObject &, sf::RenderWindow &) {}
};

class CompositeRenderComponent : public RenderComponent {
 public:
  CompositeRenderComponent() {}
  virtual ~CompositeRenderComponent() {
    BOOST_FOREACH (RenderComponent *component, components_) {
      delete component;
    }
  }

  virtual void AddComponent(RenderComponent *component) {
    components_.push_back(component);
  }
  

  virtual void Render(GameObject &game_object, sf::RenderWindow &window) {
    BOOST_FOREACH (RenderComponent *component, components_) {
      component->Render(game_object, window);
    }
  }

  void SendMessage(GameObject &obj, const Message &msg) {
    BOOST_FOREACH (RenderComponent *component, components_) {
      component->SendMessage(obj, msg);
    }
  }

 private:
  std::list<RenderComponent*> components_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_COMPONENTS_RENDER_COMPONENT_H_
