#ifndef DWARVESVERSUSGOBLINS_SRC_COMPONENTS_EVENT_COMPONENT_H_
#define DWARVESVERSUSGOBLINS_SRC_COMPONENTS_EVENT_COMPONENT_H_

#include <list>
#include <boost/foreach.hpp>

#include "components/component.h"

namespace dvg {

class Entity;

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

 private:
  std::list<EventComponent*> components_;
};

}  // namespace dvg

#endif  // DWARVESVERSUSGOBLINS_SRC_COMPONENTS_RENDER_COMPONENT_H_
