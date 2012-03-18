#include "map/entity/entity.h"

#include "map/entity/entity_manager.h"

namespace dvg {

Entity::Entity(EntityManager &manager,
               EventComponent *event_component,
               LogicComponent *logic_component,
               Ogre::Vector2 position,
               Ogre::Vector2 velocity,
               double angle)
    : manager_(manager),
      event_component_(event_component),
      logic_component_(logic_component),
      position_(position),
      velocity_(velocity),
      angle_(angle),
      active_(true) {
  if (event_component_) {
    event_component_->Init(*this);
  } else {
    event_component_ = new EmptyEventComponent();
  }

  if (logic_component_) {
    logic_component_->Init(*this);
  } else {
    logic_component_ = new EmptyLogicComponent();
  }
}

Entity::~Entity() {
  delete event_component_;
  delete logic_component_;
}

void Entity::Destroy() {
  active_ = false;
  manager_.NotifyDestroyed(*this);
}

}  // namespace dvg
