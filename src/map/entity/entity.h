#ifndef DWARVESVSGOBLINS_SRC_MAP_ENTITY_ENTITY_H_
#define DWARVESVSGOBLINS_SRC_MAP_ENTITY_ENTITY_H_

#include "fmw/ogre_framework.h"

#include "components/event_component.h"
#include "components/logic_component.h"

namespace dvg {

class EntityManager;

class Entity {
 public:
  Entity(EntityManager &manager,
         EventComponent *event_component,
         LogicComponent *logic_component,
         Ogre::Vector2 position,
         Ogre::Vector2 velocity,
         double angle);
  virtual ~Entity();

  void Destroy();

  const Ogre::Vector2 &position() const { return position_; }
  const Ogre::Vector2 &velocity() const { return velocity_; }
  double angle() const { return angle_; }
  bool active() const { return active_; }

  void set_position(const Ogre::Vector2 &position) { position_ = position; }
  void set_velocity(const Ogre::Vector2 &velocity) { velocity_ = velocity; }
  void set_angle(double angle) { angle_ = angle; }

  void Update() {
    logic_component_->Update(*this);
  }

 private:
  //TODO: Add Ogre::Entity
  EntityManager &manager_;
  EventComponent *event_component_;
  LogicComponent *logic_component_;

  Ogre::Vector2 position_;
  Ogre::Vector2 velocity_;

  double angle_;

  bool active_;
};

}  // namespace dvg

#endif  // DWARVESVSGOBLINS_SRC_MAP_ENTITY_ENTITY_H_
