#include "graphics/map_renderer.h"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "utils/game_object.h"
#include "game/map_logic.h"

namespace dvg {
namespace graphics {

MapRenderer::MapRenderer(game::MapLogic &map_logic)
 : map_logic_(map_logic) {
  
}

MapRenderer::~MapRenderer() {

}

void MapRenderer::Init(utils::GameObject &) {

}

void MapRenderer::Render(utils::GameObject &, 
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
      offset = y * map_logic_.size().x() + x;
      if (offset >= 0 && (uint32_t)offset < map_logic_.tiles().size())
        map_logic_.tiles()[offset]->Render(window);
    }
  }
}

}  // namespace graphics
}  // namespace dvg
