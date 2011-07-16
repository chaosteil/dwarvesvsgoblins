#include "graphics/components/map_render_component.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "utils/game_object.h"
#include "game/components/map_logic_component.h"
#include <iostream>

namespace dvg {
namespace graphics {

MapRenderComponent::MapRenderComponent(game::MapLogicComponent &logic_component)
 : logic_component_(logic_component) {
  
}

MapRenderComponent::~MapRenderComponent() {

}

void MapRenderComponent::Init(utils::GameObject &) {

}

void MapRenderComponent::Render(utils::GameObject &, 
                                sf::RenderWindow &window) {
  sf::FloatRect view_rect = window.GetView().GetRect();
  view_rect.Top /= base_size();
  view_rect.Bottom /= base_size();
  view_rect.Left /= base_size();
  view_rect.Right /= base_size();
  int offset;
  for (int y = view_rect.Top; y < view_rect.Bottom; y++) {
    for (int x = view_rect.Left; x < view_rect.Right; x++) {
      offset = y * logic_component_.size().x() + x;
      if (offset >= 0 && (uint32_t)offset < logic_component_.tiles().size())
        logic_component_.tiles()[offset]->Render(window);
    }
  }
}

}  // namespace graphics
}  // namespace dvg
