#ifndef DWARVESVSGOBLINS_SRC_MAP_MAP_H_
#define DWARVESVSGOBLINS_SRC_MAP_MAP_H_

#include "map/tile.h"

#include <vector>

namespace dvg {

class Map {
 public:
  Map();
  virtual ~Map();

  // TODO(ZadrraS): Implement everything for the map class (using Ogre types)

 private:
  std::vector<Tile *> tiles_;
};

}  // namespace dvg

#endif  // DWARVESVSGOBLINS_SRC_MAP_MAP_H_
