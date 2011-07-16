#ifndef DVG_SRC_UTILS_MAP_LOADER_H_
#define DVG_SRC_UTILS_MAP_LOADER_H_

#include <iostream>

namespace dvg {
namespace utils {

class MapData;

class MapLoader{
	
	static const std::string map_extension;
	static const std::string map_folder;
	
	public:
		MapLoader();
		~MapLoader();

		MapData *Load(std::string &map_name);
};

} // namespace utils
} // namespace dvg

#endif
