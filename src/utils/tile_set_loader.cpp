#include "utils/tile_set_loader.h"
#include "utils/tile_set_data.h"

#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/exceptions.hpp>

// TODO exceptioen handling

namespace dvg {
namespace utils {

TileSetLoader::TileSetLoader(){}

TileSetLoader::~TileSetLoader(){}

TileSetData *TileSetLoader::Load(const std::string &path){
  try {
    boost::property_tree::ptree root;
    boost::property_tree::json_parser::read_json(path, root);
  
    TileSetData *tile_set_data = new TileSetData();

    tile_set_data->set_name(root.get<std::string>("name"));

	  const boost::property_tree::ptree &tile_data = root.get_child("tiles");
	  typedef std::pair<const std::string, boost::property_tree::ptree> ptree_pair;
		
	  BOOST_FOREACH(const ptree_pair &tile, tile_data){
      std::string path = tile.second.get<std::string>("path");
    
      const boost::property_tree::ptree &attribute_data = tile.second.get_child("attributes");
      uint8_t flags = 0;
    
      BOOST_FOREACH(const ptree_pair &attribute, attribute_data){
	      if (attribute.second.get_value<std::string>() == "solid"){
          flags |= 1;
        }else if (attribute.second.get_value<std::string>() == "water"){
          flags |= 2;
        }else if (attribute.second.get_value<std::string>() == "lava"){
          flags |= 4;
        }else if (attribute.second.get_value<std::string>() == "diggable"){
          flags |= 8;
        }else if (attribute.second.get_value<std::string>() == "claimable"){
          flags |= 16;
        }
      }
    
      tile_set_data->AddTile(path, flags);
    }

    return tile_set_data;
  }catch(boost::property_tree::ptree_error &error){
    return NULL;
  }
}

} // namespace utils
} // namespace dvg
