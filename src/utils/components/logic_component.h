#ifndef DVG_SRC_UTILS_COMPONENTS_LOGIC_COMPONENT_H_
#define DVG_SRC_UTILS_COMPONENTS_LOGIC_COMPONENT_H_

#include <list>
#include <boost/foreach.hpp>

namespace dvg {
namespace utils {

class GameObject;

class LogicComponent {
 public:
  virtual ~LogicComponent() {}
  virtual void Init(GameObject &) {}

  virtual void Update(GameObject &game_object) = 0;

 protected:
  LogicComponent() {}
};

class EmptyLogicComponent : public LogicComponent {
 public:
  EmptyLogicComponent() {}
  virtual ~EmptyLogicComponent() {}

  virtual void Update(GameObject &) {}
};

class CompositeLogicComponent : public LogicComponent {
 public:
  CompositeLogicComponent() {}
  virtual ~CompositeLogicComponent() {
    BOOST_FOREACH (LogicComponent *component, components_) {
      delete component;
    }
  }

  virtual void AddComponent(LogicComponent *component) {
    components_.push_back(component);
  }

  virtual void Update(GameObject &game_object) {
    BOOST_FOREACH (LogicComponent *component, components_) {
      component->Update(game_object);
    }
  }

 private:
  std::list<LogicComponent*> components_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_COMPONENTS_LOGIC_COMPONENT_H_
