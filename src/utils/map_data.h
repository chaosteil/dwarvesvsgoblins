#ifndef DVG_SRC_UTILS_MAP_DATA_H_
#define DVG_SRC_UTILS_MAP_DATA_H_

#include <iostream>
#include <vector>

#include <utils/vector2d.h>

namespace dvg {
namespace utils {


class MapData{

 public:
  MapData();
  virtual ~MapData();

  const std::string &get_map_name() const { return map_name_; }
  const std::string &get_map_type() const { return map_type_; }
	const std::string &get_tile_set() const { return tile_set_; }
	const std::vector<Vector2d> &get_start_positions() const { return start_positions_; }
	const std::vector<int> &get_tiles() const { return tiles_; }
  const int &get_width() const { return width_; }
	const int &get_height() const { return height_; }
	int get_size() { return width_ * height_; }
	void set_name(const std::string &name){ map_name_ = name; }
	void set_type(const std::string &type) { map_type_ = type; }
	void set_tile_set(const std::string &tile_set) { tile_set_ = tile_set; }
	void set_width(const int &width) { width_ = width; }
	void set_height(const int &height) { height_ = height; }
	void set_tiles(const std::vector<int> &tiles) { tiles_ = tiles; }	

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
