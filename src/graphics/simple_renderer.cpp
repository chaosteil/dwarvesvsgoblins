#include "graphics/simple_renderer.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "utils/game_object.h"

namespace dvg {
namespace graphics {

SimpleRenderer::SimpleRenderer(const sf::Image &texture)
  : sprite_(texture) {
  sprite_.SetScale(standard_scale(), standard_scale());
}

SimpleRenderer::~SimpleRenderer() {

}

void SimpleRenderer::Init(utils::GameObject &) {
  sprite_.SetBlendMode(sf::Blend::None);
}

void SimpleRenderer::Render(utils::GameObject &game_object, 
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

const sf::Sprite &SimpleRenderer::sprite() const {
  return sprite_;
}
  
}  // namespace graphics
}  // namespace dvg