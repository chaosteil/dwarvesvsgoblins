#include "graphics/map_renderer.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "game/tile.h"
#include "game/map.h"
#include "graphics/resource_manager.h"

namespace dvg {
namespace graphics {

MapRenderer::MapRenderer(ResourceManager &resource_manager, 
                         const game::Map &map) : map_(map) {
  for (int y = 0; y < map_.height(); y++) {
    for (int x = 0; x < map_.width(); x++) {
      char tile_type = map_.data(utils::Vector2d(x, y)).data();
      std::string tile_texture_name;

      if (tile_type == 1) {
        tile_texture_name = "tiles/dirt.png";
      } else if (tile_type == 2) {
        tile_texture_name = "tiles/grass.png";
      } else {
        tile_texture_name = "tiles/black.png";
      }
 
      tile_sprites_.push_back(
        sf::Sprite(resource_manager.GetTexture(tile_texture_name),
                   sf::Vector2f(x * 32, y * 32),
                   sf::Vector2f(32, 32)));
    }
  }
}

MapRenderer::~MapRenderer() {}
  
void MapRenderer::Render(sf::RenderWindow &window) const {
  sf::FloatRect view_rectangle = window.GetView().GetRect();
  view_rectangle.Left -= 64;
  view_rectangle.Top -= 64;
  view_rectangle.Right += 64;
  view_rectangle.Bottom += 64;
  for (size_t i = 0; i < tile_sprites_.size(); i++) {
    if (view_rectangle.Contains(tile_sprites_[i].GetPosition().x, 
                                tile_sprites_[i].GetPosition().y)) {
      window.Draw(tile_sprites_[i]);
    }
  }
}

}  // namespace graphics
}  // namespace dvg
