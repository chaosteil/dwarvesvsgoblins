#include "graphics/simple_render_component.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "utils/components/game_object.h"

namespace dvg {
namespace graphics {

SimpleRenderComponent::SimpleRenderComponent(const sf::Image &texture, 
                                             sf::RenderWindow &window) 
  : sprite_(texture), window_(window) {
  
}

SimpleRenderComponent::~SimpleRenderComponent() {
  
}

void SimpleRenderComponent::Init(utils::GameObject &) {
  sprite_.SetBlendMode(sf::Blend::None);
}

void SimpleRenderComponent::Render(utils::GameObject &game_object) {
  sf::FloatRect object_rect(game_object.position().pos().x(),
                             game_object.position().pos().y(),
                             game_object.position().pos().x() + 
                             game_object.position().size().x(),
                             game_object.position().pos().y() +
                             game_object.position().size().y());
                             
  if (window_.GetView().GetRect().Intersects(object_rect)) {                              
    sprite_.SetPosition(game_object.position().pos().x(), 
                        game_object.position().pos().y());
    sprite_.SetScale(game_object.position().size().x(), 
                     game_object.position().size().y());
    sprite_.SetRotation(game_object.angle());
    window_.Draw(sprite_);
  }
}

const sf::Sprite &SimpleRenderComponent::sprite() const {
  return sprite_;
}
  
}  // namespace graphics
}  // namespace dvg