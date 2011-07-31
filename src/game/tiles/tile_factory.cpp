#include "game/tiles/tile_factory.h"

#include <boost/foreach.hpp>

namespace dvg {
namespace game {

TileFactory::TileFactory() {}

TileFactory::~TileFactory() {
  BOOST_FOREACH (Factories::value_type factory, factories_) {
    delete factory.second;
  }
}

void TileFactory::AddFactory(const std::string &name, Factory *factory) {
  Factories::iterator it = factories_.find(name);

  if (it != factories_.end()) {
    delete it->second;
  }

  factories_[name] = factory;
}

Tile *TileFactory::CreateTile(const std::string &name) {
  Factories::iterator it = factories_.find(name);

  if (it == factories_.end()) {
    return NULL;
  }

  return it->second->CreateTile();
}

}  // namespace game
}  // namespace dvg
