#include "game/map_logic.h"

#include "utils/game_object.h"
#include "game/tiles/ground_tile.h"
#include "game/tiles/wall_tile.h"
#include "graphics/resource_manager.h"
#include "graphics/simple_renderer.h"
#include "utils/scene_manager.h"
#include "utils/map_data.h"
#include "utils/map_loader.h"

namespace dvg {
namespace game {
  
static graphics::ResourceManager resource_manager;

MapLogic::MapLogic(const utils::Vector2d &size, 
                   utils::SceneManager &scene_manager) 
 : size_(size), scene_manager_(scene_manager) {

}

MapLogic::~MapLogic() {
  BOOST_FOREACH(utils::GameObject *tile, tiles_) {
    delete tile;
  }
}

void MapLogic::Init(utils::GameObject &) {
  utils::MapLoader map_loader;
  utils::MapData *current_map = map_loader.Load("../data/maps/bigmap.json");
  
  std::string tile_texture_name;
  utils::Vector2d tile_size(1.0f, 1.0f);
  utils::Vector2d tile_pos(0.0f, 0.0f);
  for (int y = 0; y < size_.y(); y++) {
    for (int x = 0; x < size_.x(); x++) {
      char tile_type = current_map->get_tiles().at(x + y * current_map->get_width());
          
      game::Tile *logic;
      if (tile_type == 1) {
        tile_texture_name = "tiles/stone.png";
        logic = new game::WallTile();
      } else if (tile_type == 2) {
        tile_texture_name = "tiles/dirt.png";
        logic = new game::GroundTile();
      } else {
        tile_texture_name = "tiles/black.png";
        logic = new game::WallTile();
      }

      graphics::SimpleRenderer *render = 
        new graphics::SimpleRenderer(
          resource_manager.GetTexture(tile_texture_name));
      
      tile_pos.set_x(x);
      tile_pos.set_y(y);
      utils::GameObject *tile = 
        new utils::GameObject(scene_manager_,
                              NULL, logic, render, NULL, 
                              utils::Rectangle(tile_pos, tile_size),
                              utils::Vector2d(0.0f, 0.0f),
                              0.0f);
      tiles_.push_back(tile);
    }
  }
  
  delete current_map;
}

void MapLogic::Update(utils::GameObject &) {
  BOOST_FOREACH(utils::GameObject *tile, tiles_) {
    tile->Update();
  }
}

std::vector<utils::GameObject *> &MapLogic::tiles() {
  return tiles_;
}

utils::Vector2d MapLogic::size() const {
  return size_;
}

}  // namespace game
}  // namespace dvg
