#ifndef DVG_UTILS_TILE_SET_DATA_H_
#define DVG_UTILS_TILE_SET_DATA_H_

#include <iostream>
#include <stdint.h>
#include <vector>

#include "utils/tile.h"

namespace dvg {
namespace utils {

class Tile;

class TileSetData{
 public:
  TileSetData();
  virtual ~TileSetData();
    
  const std::vector<Tile> &get_tiles() const { return tiles_; }
  const std::string &get_name() const { return name_; }

  void set_name(const std::string &name){ name_ = name; }
  
  void AddTile(const std::string &path, const uint8_t flags);
 
 private: 
  std::string name_;
  std::vector<Tile> tiles_;
    
};

} // namespace utils
} // namespace dvg


#endif
