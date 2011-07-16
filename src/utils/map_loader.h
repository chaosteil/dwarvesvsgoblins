#ifndef DVG_SRC_UTILS_MAP_LOADER_H_
#define DVG_SRC_UTILS_MAP_LOADER_H_

#include <iostream>

namespace dvg {
namespace utils {

class MapData;

class MapLoader{
	public:
		MapLoader();
		~MapLoader();

		MapData *Load(const std::string &map_name);
};

} // namespace utils
} // namespace dvg

#endif
