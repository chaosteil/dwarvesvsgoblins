#include "graphics/resource_manager.h"

namespace dvg {
namespace graphics {
  
ResourceManager::ResourceManager() {
  
}

ResourceManager::~ResourceManager() {
  
}

const sf::Image &ResourceManager::GetTexture(const std::string &texture_name) {
  boost::unordered_map<std::string, sf::Image>::iterator texture_it = textures_.find(texture_name);
  if (texture_it != textures_.end()) {
    return texture_it->second;
  } else {
    sf::Image texture;
    texture.LoadFromFile("../data/" + texture_name);
    textures_[texture_name] = texture;
    texture.SetSmooth(false);
    
    return textures_[texture_name];
  }
}
  
}  // graphics
}  // dvg
