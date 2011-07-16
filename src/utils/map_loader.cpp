#include "utils/map_loader.h"

#include <fstream> 
#include <vector>
#include <utility>

#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "utils/map_data.h"

namespace dvg {
namespace utils {

const std::string MapLoader::map_extension = ".json";
const std::string MapLoader::map_folder = "../../../data/maps/";

MapLoader::MapLoader(){}

MapLoader::~MapLoader(){}

MapData *MapLoader::Load(std::string &map_name){
	std::string map_path = map_folder + map_name + map_extension;
	
	boost::property_tree::ptree root;
	MapData *map_data = new MapData();
	
	boost::property_tree::json_parser::read_json(map_path, root);

	map_data->SetName(root.get<std::string>("name"));
	map_data->SetType(root.get<std::string>("type"));
	map_data->SetTileSet(root.get<std::string>("tile_set"));
	map_data->SetWidth(root.get<int>("width"));
	map_data->SetHeight(root.get<int>("height"));	

	int width = map_data->GetWidth();
	int height = map_data->GetHeight();

	{
		const boost::property_tree::ptree &player_data = root.get_child("players");
		typedef std::pair<const std::string, boost::property_tree::ptree> ptree_pair;
		
		BOOST_FOREACH(const ptree_pair &player, player_data){
			map_data->AddStartPosition((double)player.second.get<int>("x"), (double)player.second.get<int>("y"));
		}
	}

	{
		const boost::property_tree::ptree &tile_data = root.get_child("tiles");
		boost::property_tree::ptree::const_iterator it = tile_data.begin();

		std::vector<int> tiles;

		for (int x = 0; x < width; x++){
			for (int y = 0; y < height; y++){
				tiles.push_back(it->second.get_value<int>());
				it++;
			}
		}

		map_data->SetTiles(tiles);
	}

	return map_data;
}

} // namespace utils
} // namespace dvg


