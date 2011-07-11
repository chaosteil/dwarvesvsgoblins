#ifndef DVG_SRC_UTILS_COMPONENTS_EVENT_COMPONENT_H_
#define DVG_SRC_UTILS_COMPONENTS_EVENT_COMPONENT_H_

#include <list>
#include <boost/foreach.hpp>

namespace dvg {
namespace utils {

class GameObject;

class EventComponent {
 public:
  virtual ~EventComponent() {}
  virtual void Init(GameObject &) {}

  // TODO: Message handling

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

  // TODO: Distribute message

 private:
  std::list<EventComponent*> components_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_COMPONENTS_RENDER_COMPONENT_H_
