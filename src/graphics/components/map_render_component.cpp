#include "graphics/components/map_render_component.h"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "utils/game_object.h"
#include "game/components/map_logic_component.h"

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
  sf::View view = window.GetView();
  sf::FloatRect view_rect;
  view_rect.Top = (view.GetCenter().y - view.GetSize().y / 2) / base_size();
  view_rect.Left = (view.GetCenter().x - view.GetSize().x / 2) / base_size();
  view_rect.Height = view.GetSize().y / base_size();
  view_rect.Width  = view.GetSize().x / base_size();
  
  int offset;
  for (int y = view_rect.Top; y < view_rect.Top + view_rect.Height; y++) {
    for (int x = view_rect.Left; x < view_rect.Left + view_rect.Width; x++) {
      offset = y * logic_component_.size().x() + x;
      if (offset >= 0 && (uint32_t)offset < logic_component_.tiles().size())
        logic_component_.tiles()[offset]->Render(window);
    }
  }
}

}  // namespace graphics
}  // namespace dvg
