#include "map_data.h"

#include "vector2d.h"

namespace dvg {
namespace utils {

MapData::MapData(){}

MapData::~MapData(){}

void MapData::AddStartPosition(const double &x, const double &y){
	Vector2d start_position(x, y);
	start_positions_.push_back(start_position);
}

void MapData::AddTile(const int &x, const int &y, const int &tile){	
	tiles_[x + y * width_] = tile;
}

} // namespace utils
} // namespace dvg

