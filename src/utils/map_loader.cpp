#include "utils/map_loader.h"

#include <fstream> 
#include <vector>
#include <utility>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/exceptions.hpp>
#include <boost/foreach.hpp>

#include "utils/map_data.h"

namespace dvg {
namespace utils {

MapLoader::MapLoader(){}

MapLoader::~MapLoader(){}

MapData *MapLoader::Load(const std::string &map_path){
  try {
	  boost::property_tree::ptree root;
	  boost::property_tree::json_parser::read_json(map_path, root);

    MapData *map_data = new MapData();
	
	  map_data->set_name(root.get<std::string>("name"));
	  map_data->set_type(root.get<std::string>("type"));
	  map_data->set_tile_set(root.get<std::string>("tile_set"));
	  map_data->set_width(root.get<int>("width"));
	  map_data->set_height(root.get<int>("height"));	
		
    const boost::property_tree::ptree &player_data = root.get_child("players");
		typedef std::pair<const std::string, boost::property_tree::ptree> ptree_pair;
		
		BOOST_FOREACH(const ptree_pair &player, player_data){
			map_data->AddStartPosition((double)player.second.get<int>("x"), (double)player.second.get<int>("y"));
    }

    const boost::property_tree::ptree &tile_data = root.get_child("tiles");
		boost::property_tree::ptree::const_iterator it = tile_data.begin();

		std::vector<int> tiles;

		for (int x = 0; x < map_data->get_width(); x++){
			for (int y = 0; y < map_data->get_height(); y++){
				tiles.push_back(it->second.get_value<int>());
				it++;
			}
    }

		map_data->set_tiles(tiles);
    return map_data;

  }catch(boost::property_tree::ptree_error &error){
    return NULL;
  }
}

} // namespace utils
} // namespace dvg


