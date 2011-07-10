#include "graphics/rendering_manager.h"

#include "utils/game_object.h"
#include "graphics/renderable_component.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>

namespace dvg {
namespace graphics {
  
RenderingManager::RenderingManager() {
  
}

RenderingManager::~RenderingManager() {
  
}

void RenderingManager::Render(sf::RenderWindow &window) const {
  sf::FloatRect view_rectangle = window.GetView().GetRect();
  view_rectangle.Left -= 64;
  view_rectangle.Top -= 64;
  view_rectangle.Right += 64;
  view_rectangle.Bottom += 64;
  for (std::list<RenderableComponent *>::const_iterator it = renderables_.begin();
       it != renderables_.end();
       ++it) {
      window.Draw((*it)->sprite());
  }
}

void RenderingManager::Register(utils::GameObject &game_object, 
                const sf::Image &texture,
                const sf::Vector2f &position) {
  RenderableComponent *renderable_component = 
    new RenderableComponent(*this, texture, position);
  renderables_.push_back(renderable_component);
  game_object.AddComponent(renderable_component);
}

bool RenderingManager::HasComponent(utils::GameComponent *component) const {
  return std::find(renderables_.begin(), renderables_.end(), component) != renderables_.end();
}

void RenderingManager::Cleanup(utils::GameComponent *component) {
  renderables_.erase(std::remove(renderables_.begin(), renderables_.end(), component), 
                     renderables_.end());
}
  
}  // namespace graphics
}  // namespace dvg