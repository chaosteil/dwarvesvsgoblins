#ifndef DWARVESVERSUSGOBLINS_SRC_COMPONENTS_LOGIC_COMPONENT_H_
#define DWARVESVERSUSGOBLINS_SRC_COMPONENTS_LOGIC_COMPONENT_H_

#include <list>
#include <boost/foreach.hpp>

#include "components/component.h"

namespace dvg {

class Entity;

class LogicComponent : public Component {
 public:
  virtual ~LogicComponent() {}

  virtual void Update(Entity &entity) = 0;

 protected:
  LogicComponent() {}
};

class EmptyLogicComponent : public LogicComponent {
 public:
  EmptyLogicComponent() {}
  virtual ~EmptyLogicComponent() {}

  virtual void Update(Entity &) {}
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

  virtual void Update(Entity &entity) {
    BOOST_FOREACH (LogicComponent *component, components_) {
      component->Update(entity);
    }
  }

 private:
  std::list<LogicComponent*> components_;
};

}  // namespace dvg

#endif  // DWARVESVERSUSGOBLINS_SRC_COMPONENTS_LOGIC_COMPONENT_H_
