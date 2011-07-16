#ifndef DVG_SRC_UTILS_COMPONENTS_EVENT_COMPONENT_H_
#define DVG_SRC_UTILS_COMPONENTS_EVENT_COMPONENT_H_

#include <list>
#include <boost/foreach.hpp>

#include "utils/components/component.h"

namespace dvg {
namespace utils {

class GameObject;
class Message;

class EventComponent : public Component {
 public:
  virtual ~EventComponent() {}

 protected:
  EventComponent() {}
};

class EmptyEventComponent : public EventComponent {
 public:
  EmptyEventComponent() {}
  virtual ~EmptyEventComponent() {}
};

class CompositeEventComponent : public EventComponent {
 public:
  CompositeEventComponent() {}
  virtual ~CompositeEventComponent() {
    BOOST_FOREACH (EventComponent *component, components_) {
      delete component;
    }
  }

  void AddComponent(EventComponent *component) {
    components_.push_back(component);
  }

  void SendMessage(GameObject &obj, const Message &msg) {
    BOOST_FOREACH (EventComponent *component, components_) {
      component->SendMessage(obj, msg);
    }
  }

 private:
  std::list<EventComponent*> components_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_COMPONENTS_RENDER_COMPONENT_H_
