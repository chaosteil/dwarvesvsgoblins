#ifndef DVG_SRC_GRAPHICS_MAP_RENDERER_H_
#define DVG_SRC_GRAPHICS_MAP_RENDERER_H_

#include <vector>
#include <SFML/Graphics/Sprite.hpp>

namespace sf { class RenderWindow; }

namespace dvg {
  
namespace game { class Map; }

namespace graphics {
class ResourceManager;

class MapRenderer {
 public:
  MapRenderer(ResourceManager &resource_manager, const game::Map &map);
  virtual ~MapRenderer();
   
  void Render(sf::RenderWindow &window) const;
   
 private:
  const game::Map &map_;
  std::vector<sf::Sprite> tile_sprites_;
};

}  // namespace graphics
}  // namespace dvg

#endif  // DVG_SRC_GRAPHICS_MAP_RENDERER_H_
