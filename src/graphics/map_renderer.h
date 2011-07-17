#ifndef DVG_SRC_GRAPHICS_MAP_RENDERER_H_
#define DVG_SRC_GRAPHICS_MAP_RENDERER_H_

#include "utils/components/render_component.h"

#include <SFML/Graphics/Sprite.hpp>

namespace sf { class RenderWindow; }

namespace dvg {
namespace utils { class GameObject; }
namespace game { class MapLogic; }
namespace graphics {

class MapRenderer : public utils::RenderComponent {
 public:
  MapRenderer(game::MapLogic &map_logic);
  virtual ~MapRenderer();
  
  void Init(utils::GameObject &game_object);
  void Render(utils::GameObject &game_object, sf::RenderWindow &window);
  
 private:
   game::MapLogic &map_logic_;
};

}  // namespace graphics
}  // namespace dvg

#endif  // DVG_SRC_GRAPHICS_MAP_RENDERER_H_