#ifndef DVG_SRC_GAME_MAP_H_
#define DVG_SRC_GAME_MAP_H_

#include <vector>
#include <boost/unordered_map.hpp>
#include "utils/vector2d.h"
#include "utils/quadtree.h"

namespace dvg {
namespace utils { class GameObject; class SceneManager; }
namespace game {

class Tile;

class Map {
 public:
  typedef utils::Quadtree<utils::GameObject *> ObjectTree;

  Map(const utils::Vector2d &size, utils::SceneManager &scene_manager);
  ~Map();

  Tile *tile(const utils::Vector2d &v);
  const std::vector<utils::GameObject *> &tiles() const { return tiles_; }
  ObjectTree &objects() { return objects_; }
  utils::Vector2d size() const { return size_; }

  // FIXME(Chaosteil): Automatic, please!
  void UpdatePosition(utils::GameObject *object);

  void ReplaceTile(utils::Vector2d pos, Tile *tile);

 private:
  typedef boost::unordered_map<utils::GameObject *, Tile *> LogicTiles;

  utils::SceneManager &scene_manager_;

  LogicTiles logic_tiles_;
  std::vector<utils::GameObject *> tiles_;
  ObjectTree objects_;
  utils::Vector2d size_;
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_MAP_H_
