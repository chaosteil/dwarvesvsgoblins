#ifndef DVG_SRC_GRAPHICS_MAP_RENDERER_IN_
#define DVG_SRC_GRAPHICS_MAP_RENDERER_IN_

namespace sf {
  class RenderWindow;
}

namespace dvg {
  
namespace game {
  class Map;
}

namespace graphics {

class MapRenderer {
 public:
  MapRenderer(const game::Map &map);
  virtual ~MapRenderer();
   
  void Render(sf::RenderWindow &window);
   
 private:
  const game::Map &map_;
};

}  // namespace graphics
}  // namespace dvg

#endif  // DVG_SRC_GRAPHICS_MAP_RENDERER_IN_