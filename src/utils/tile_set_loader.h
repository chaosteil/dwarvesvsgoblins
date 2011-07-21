#ifndef DVG_UTILS_TILE_SET_LOADER_H_
#define DVG_UTILS_TILE_SET_LOADER_H_

#include <iostream>

namespace dvg {
namespace utils {

class TileSetData;

class TileSetLoader{
 public: 
  TileSetLoader();
  virtual ~TileSetLoader();

  TileSetData *Load(const std::string &path);
};

} // namespace utils
} // namespace dvg

#endif
