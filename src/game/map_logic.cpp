#include "game/map_logic.h"

#include "utils/game_object.h"

namespace dvg {
namespace game {
  
MapLogic::MapLogic(const utils::Vector2d &size, 
                   utils::SceneManager &scene_manager) 
 : map_(new Map(size, scene_manager)) {

}

MapLogic::~MapLogic() {
  delete map_;
}

void MapLogic::Init(utils::GameObject &) {} 

void MapLogic::Update(utils::GameObject &) {
  BOOST_FOREACH(utils::GameObject *tile, map_->tiles()) {
    tile->Update();
  }
}

}  // namespace game
}  // namespace dvg
