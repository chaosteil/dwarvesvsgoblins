#include "utils/map_loader.h"

#include <fstream> 
#include <vector>

#include <boost/property_tree/json_parser.hpp>

#include "utils/map_data.h"

namespace dvg {
namespace utils {

const std::string MapLoader::map_extension = ".json";
const std::string MapLoader::map_folder = "../maps/";

MapLoader::MapLoader(){}

MapLoader::~MapLoader(){}

MapData *MapLoader::Load(const std::string &map_name){
	std::string map_path = map_folder + map_name + map_extension;
	
	boost::property_tree::ptree root;
	MapData *map_data = new MapData();
	
	boost::property_tree::json_parser::read_json(map_path, root);

	map_data->SetName(root.get<std::string>("name"));
	map_data->SetType(root.get<std::string>("type"));
	map_data->SetWidth(root.get<int>("width"));
	map_data->SetHeight(root.get<int>("height"));
	
	int number_of_players = root.get<int>("number_of_players");

	map_data->SetNumberOfPlayers(number_of_players);

	for (int i = 1; i <= number_of_players; i++){
		std::string player("player ");
		player += (i + 48);
		const boost::property_tree::ptree &array = root.get_child(player);
		boost::property_tree::ptree::const_iterator it = array.begin();
		int pos1 = it->second.get_value<int>();
		it++;
		int pos2 = it->second.get_value<int>();
		map_data->AddStartPosition((double)pos1, (double)pos2);
	}
	
	int width = map_data->GetWidth();
	int height = map_data->GetHeight();

	const boost::property_tree::ptree &data = root.get_child("tiles");
	boost::property_tree::ptree::const_iterator it = data.begin();

	std::vector<int> tiles;

	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			tiles.push_back(it->second.get_value<int>());
			it++;
		}
	}

	map_data->SetTiles(tiles);

	return map_data;
}

} // namespace utils
} // namespace dvg


