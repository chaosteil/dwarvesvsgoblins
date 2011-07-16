#ifndef DVG_SRC_GRAPHICS_MAP_RENDER_COMPONENT_H_
#define DVG_SRC_GRAPHICS_MAP_RENDER_COMPONENT_H_

#include "utils/components/render_component.h"

#include <SFML/Graphics/Sprite.hpp>

namespace sf { class RenderWindow; }

namespace dvg {
namespace utils { class GameObject; }
namespace game { class MapLogicComponent; }
namespace graphics {

class MapRenderComponent : public utils::RenderComponent {
 public:
  MapRenderComponent(game::MapLogicComponent &logic_component);
  virtual ~MapRenderComponent();
  
  void Init(utils::GameObject &game_object);
  void Render(utils::GameObject &game_object, sf::RenderWindow &window);
  
 private:
   game::MapLogicComponent &logic_component_;
};

}  // namespace graphics
}  // namespace dvg

#endif  // DVG_SRC_GRAPHICS_MAP_RENDER_COMPONENT_H_