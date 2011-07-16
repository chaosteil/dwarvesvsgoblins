#include "game/components/map_logic_component.h"

#include "utils/game_object.h"
#include "game/wall_tile.h"
#include "graphics/resource_manager.h"
#include "graphics/components/simple_render_component.h"
#include "utils/scene_manager.h"
#include "utils/map_data.h"
#include "utils/map_loader.h"

namespace dvg {
namespace game {
  
static graphics::ResourceManager resource_manager;

MapLogicComponent::MapLogicComponent(const utils::Vector2d &size, 
                                     utils::SceneManager &scene_manager) 
 : size_(size), scene_manager_(scene_manager) {

}

MapLogicComponent::~MapLogicComponent() {
  BOOST_FOREACH(ObjectMap::value_type &object_pair, tiles_) {
    delete object_pair.second;
  }
}

void MapLogicComponent::Init(utils::GameObject &) {
  utils::MapLoader map_loader;
  utils::MapData *current_map = map_loader.Load("../data/maps/bigmap.json");
  
  std::string tile_texture_name;
  utils::Vector2d tile_size(1.0f, 1.0f);
  utils::Vector2d tile_pos(0.0f, 0.0f);
  for (int y = 0; y < size_.y(); y++) {
    for (int x = 0; x < size_.x(); x++) {
      char tile_type = current_map->GetTiles().at(x + y * current_map->GetWidth());
          
      if (tile_type == 1) {
        tile_texture_name = "tiles/dirt.png";
      } else if (tile_type == 2) {
        tile_texture_name = "tiles/grass.png";
      } else {
        tile_texture_name = "tiles/black.png";
      }

      game::WallTileLogic *logic
        = new game::WallTileLogic(tile_type);
      game::WallTileInput *input
        = new game::WallTileInput(*logic);

      graphics::SimpleRenderComponent *render = 
        new graphics::SimpleRenderComponent(
          resource_manager.GetTexture(tile_texture_name));
      
      tile_pos.set_x(x);
      tile_pos.set_y(y);
      utils::GameObject *tile = 
        new utils::GameObject(scene_manager_,
                              input, logic, render, NULL, 
                              utils::Rectangle(tile_pos, tile_size),
                              utils::Vector2d(0.0f, 0.0f),
                              0.0f);
      tiles_[tile_pos] = tile;
    }
  }
}

void MapLogicComponent::Update(utils::GameObject &) {
  BOOST_FOREACH(ObjectMap::value_type &object_pair, tiles_) {
    object_pair.second->Update();
  }
}

MapLogicComponent::ObjectMap MapLogicComponent::tiles() {
  return tiles_;
}

utils::Vector2d MapLogicComponent::size() const {
  return size_;
}

}  // namespace game
}  // namespace dvg
