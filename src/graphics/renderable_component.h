#ifndef DVG_SRC_GRAPHICS_RENDERABLE_COMPONENT_H_
#define DVG_SRC_GRAPHICS_RENDERABLE_COMPONENT_H_

#include "utils/game_component.h"

#include <SFML/Graphics/Sprite.hpp>

namespace dvg {
namespace utils { class GameComponentManager; }
namespace graphics {

class RenderableComponent : public utils::GameComponent {
 public:
  RenderableComponent(utils::GameObject &game_object,
                      utils::GameComponentManager &manager, 
                      const sf::Image &texture,
                      const sf::Vector2f &position);
  ~RenderableComponent();
  
  const sf::Sprite &sprite() const;
  
 private:
  sf::Sprite sprite_;
};

}  // namespace graphics
}  // namespace dvg

#endif  // DVG_SRC_GRAPHICS_RENDERABLE_COMPONENT_H_
