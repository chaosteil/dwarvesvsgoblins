#include "utils/tile_set_data.h"
#include "utils/tile.h"

namespace dvg {
namespace utils {

TileSetData::TileSetData(){}

TileSetData::~TileSetData(){}

void TileSetData::AddTile(const std::string &path, const uint8_t flags){
    Tile new_tile(path, flags);
    tiles_.push_back(new_tile);
}

} // namespace utils
} // namespace dvg
