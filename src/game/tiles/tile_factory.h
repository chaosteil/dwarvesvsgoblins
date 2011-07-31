#ifndef DVG_SRC_GAME_TILES_TILE_FACTORY_H_
#define DVG_SRC_GAME_TILES_TILE_FACTORY_H_

#include <string>
#include <boost/unordered_map.hpp>

namespace dvg {
namespace game {

class Tile;

class TileFactory {
 public:
  class Factory {
   public:
    virtual ~Factory() {}

    virtual Tile *CreateTile() = 0;

   protected:
    Factory() {}
  };

  TileFactory();
  ~TileFactory();

  void AddFactory(const std::string &name, Factory*);

  Tile *CreateTile(const std::string &name);

 private:
  typedef boost::unordered_map<std::string, Factory*> Factories;
  Factories factories_;
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_TILES_TILE_FACTORY_H_
