#ifndef DVG_SRC_GRAPHICS_RESOURCE_MANAGER_H_
#define DVG_SRC_GRAPHICS_RESOURCE_MANAGER_H_

#include <boost/unordered_map.hpp>
#include <SFML/Graphics/Image.hpp>

namespace dvg {
namespace graphics {

class ResourceManager {
 public:
  ResourceManager();
  virtual ~ResourceManager();
  
  const sf::Image &GetTexture(const std::string &texture_name);
  
 private:
  boost::unordered_map<std::string, sf::Image> textures_;
};
  
}  // graphics
}  // dvg

#endif  // DVG_SRC_GRAPHICS_RESOURCE_MANAGER_H_