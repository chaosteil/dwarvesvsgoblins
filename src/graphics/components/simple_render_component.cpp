#include "graphics/components/simple_render_component.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "utils/game_object.h"

namespace dvg {
namespace graphics {

SimpleRenderComponent::SimpleRenderComponent(const sf::Image &texture, 
                                             sf::RenderWindow &window) 
  : sprite_(texture), window_(window) {
  sprite_.SetScale(standard_scale(), standard_scale());
}

SimpleRenderComponent::~SimpleRenderComponent() {
  
}

void SimpleRenderComponent::Init(utils::GameObject &) {
  sprite_.SetBlendMode(sf::Blend::None);
}

void SimpleRenderComponent::Render(utils::GameObject &game_object) {
  sf::Vector2f real_pos(game_object.position().pos().x() * sprite_.GetSize().x,
                        game_object.position().pos().y() * sprite_.GetSize().y);
  
  sf::FloatRect object_rect(real_pos.x, real_pos.y, 
                            real_pos.x + sprite_.GetSize().x,
                            real_pos.y + sprite_.GetSize().y);
                          
  if (window_.GetView().GetRect().Intersects(object_rect)) {                              
    sprite_.SetPosition(real_pos.x, real_pos.y);
    sprite_.SetRotation(game_object.angle());
    window_.Draw(sprite_);
  }
}

const sf::Sprite &SimpleRenderComponent::sprite() const {
  return sprite_;
}
  
}  // namespace graphics
}  // namespace dvg
