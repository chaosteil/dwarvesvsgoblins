#include "graphics/renderable_component.h"

#include "utils/game_component_manager.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace dvg {
namespace graphics {

RenderableComponent::RenderableComponent(utils::GameComponentManager &manager, 
                                         const sf::Image &texture,
                                         const sf::Vector2f &position) 
  : GameComponent(manager), sprite_(texture, sf::Vector2f(position.x, position.y)) {
  sprite_.Resize(32, 32);
}

RenderableComponent::~RenderableComponent() {
  
}

const sf::Sprite &RenderableComponent::sprite() const {
  return sprite_;
}

}  // namespace graphics
}  // namespace dvg