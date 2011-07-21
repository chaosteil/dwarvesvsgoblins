#ifndef DVG_SRC_GRAPHICS_SIMPLE_RENDER_COMPONENT_H_
#define DVG_SRC_GRAPHICS_SIMPLE_RENDER_COMPONENT_H_

#include "utils/components/render_component.h"

#include <SFML/Graphics/Sprite.hpp>

namespace sf { class RenderWindow; }

namespace dvg {
namespace utils { class GameObject; }
namespace graphics {

class SimpleRenderComponent : public utils::RenderComponent {
 public:
  SimpleRenderComponent(const sf::Image &texture);
  virtual ~SimpleRenderComponent();
  virtual void Init(utils::GameObject &);

  virtual void Render(utils::GameObject &game_object, sf::RenderWindow &window);

  const sf::Sprite &sprite() const;
  
 private:
  sf::Sprite sprite_;
};

}  // namespace graphics
}  // namespace dvg

#endif  // DVG_SRC_GRAPHICS_SIMPLE_RENDER_COMPONENT_H_
