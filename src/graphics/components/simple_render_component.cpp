#include "graphics/components/simple_render_component.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "utils/game_object.h"
#include <iostream>

namespace dvg {
namespace graphics {

SimpleRenderComponent::SimpleRenderComponent(const sf::Image &texture)
  : sprite_(texture) {
  sprite_.SetScale(standard_scale(), standard_scale());
}

SimpleRenderComponent::~SimpleRenderComponent() {

}

void SimpleRenderComponent::Init(utils::GameObject &) {
  sprite_.SetBlendMode(sf::Blend::None);
}

void SimpleRenderComponent::Render(utils::GameObject &game_object, 
                                   sf::RenderWindow &window) {
  sf::Vector2f real_pos(game_object.position().pos().x() * sprite_.GetSize().x,
                        game_object.position().pos().y() * sprite_.GetSize().y);
  
  sf::FloatRect object_rect(real_pos.x, real_pos.y, 
                            sprite_.GetSize().x,
                            sprite_.GetSize().y);

  sprite_.SetPosition(real_pos.x, real_pos.y);
  sprite_.SetRotation(game_object.angle());
  window.Draw(sprite_);
}

const sf::Sprite &SimpleRenderComponent::sprite() const {
  return sprite_;
}
  
}  // namespace graphics
}  // namespace dvg
