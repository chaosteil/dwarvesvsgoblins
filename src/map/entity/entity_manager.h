#ifndef DWARVESVSGOBLINS_SRC_MAP_ENTITY_ENTITY_MANAGER_H_
#define DWARVESVSGOBLINS_SRC_MAP_ENTITY_ENTITY_MANAGER_H_

namespace dvg {

class Entity;

// dummy class for compilation
class EntityManager {
 public:
  EntityManager() {}
  virtual ~EntityManager() {}

  void NotifyDestroyed(Entity &entity) {}
};

}  // namespace dvg

#endif  // DWARVESVSGOBLINS_SRC_MAP_ENTITY_ENTITY_MANAGER_H_
