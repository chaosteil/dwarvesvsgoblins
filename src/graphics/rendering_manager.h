#ifndef DVG_SRC_GRAPHICS_RENDERING_MANAGER_H_
#define DVG_SRC_GRAPHICS_RENDERING_MANAGER_H_

#include "utils/game_component_manager.h"

#include <SFML/System/Vector2.hpp>
#include <list>

namespace sf { 
class RenderWindow; 
class Image;
}

namespace dvg {
namespace utils {
class GameObject;
class GameComponent;
}
namespace graphics {
class RenderableComponent;
  
class RenderingManager : public utils::GameComponentManager {
 public:
  RenderingManager();
  ~RenderingManager();
  
  void Render(sf::RenderWindow &window) const;
  void Register(utils::GameObject &game_object, 
                const sf::Image &texture,
                const sf::Vector2f &position);
  
  bool HasComponent(utils::GameComponent *component) const;
  void Cleanup(utils::GameComponent *component);
  
 private:
  std::list<RenderableComponent *> renderables_;
  
};

}  // namespace graphics
}  // namespace dvg

#endif  // DVG_SRC_GRAPHICS_RENDERING_MANAGER_H_