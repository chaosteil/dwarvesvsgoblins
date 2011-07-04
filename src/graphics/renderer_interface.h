#ifndef DVG_SRC_GRAPHICS_RENDERER_INTERFACE_H_
#define DVG_SRC_GRAPHICS_RENDERER_INTERFACE_H_

namespace sf { class RenderWindow; }

namespace dvg {
namespace graphics {
  
class RendererInterface {
 public:
  void Render(sf::RenderWindow &window) const;   
};

}  // namespace graphics
}  // namespace dvg

#endif  // DVG_SRC_GRAPHICS_RENDERER_INTERFACE_H_