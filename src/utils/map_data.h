#ifndef DVG_SRC_UTILS_MAP_DATA_H_
#define DVG_SRC_UTILS_MAP_DATA_H_

#include <iostream>
#include <vector>

namespace dvg {
namespace utils {

class Vector2d;

class MapData{

	public:
		MapData();
		~MapData();

		const std::string &GetMapName() const { return map_name_; }
		const std::string &GetMapType() const { return map_type_; }
		const std::string &GetTileSet() const { return tile_set_; }
		const std::vector<Vector2d> &GetStartPositions() const { return start_positions_; }
		const std::vector<int> &GetTiles() const { return tiles_; }
		const int &GetWidth() const { return width_; }
		const int &GetHeight() const { return height_; }
		int GetSize() { return width_ * height_; }
		void SetName(const std::string &name){ map_name_ = name; }
		void SetType(const std::string &type) { map_type_ = type; }
		void SetTileSet(const std::string &tile_set) { tile_set_ = tile_set; }
		void SetWidth(const int &width) { width_ = width; }
		void SetHeight(const int &height) { height_ = height; }
		void SetTiles(const std::vector<int> &tiles) { tiles_ = tiles; }	

		void AddStartPosition(const double &x, const double &y);
		void AddTile(const int &x, const int &y, const int &tile);

	private:
		std::string map_name_;
		std::string map_type_;
		std::string tile_set_;

		int width_, height_;
		
		std::vector<Vector2d> start_positions_;
		std::vector<int> tiles_;
};

} // namespace utils
} // namespace dvg


#endif
