#include "graphics/map_renderer.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "game/tile.h"
#include "game/map.h"

namespace dvg {
namespace graphics {

MapRenderer::MapRenderer(const game::Map &map) : map_(map) {}

MapRenderer::~MapRenderer() {}
  
void MapRenderer::Render(sf::RenderWindow &window) {
  for (int y = 0; y < map_.height(); y++) {
    for (int x = 0; x < map_.width(); x++) {
      sf::Sprite tile_sprite;
      tile_sprite.SetColor(sf::Color(0, 255 * map_.data(x, y).data(), 0));
      tile_sprite.SetX(x * 32);
      tile_sprite.SetY(y * 32);
      tile_sprite.SetCenter(0, 0);
      tile_sprite.Resize(32, 32);
      
      window.Draw(tile_sprite);
    }
  }
}

}  // namespace graphics
}  // namespace dvg
