#ifndef DVG_UTILS_TILE_DATA_H_
#define DVG_UTILS_TILE_DATA_H_

#include <iostream>
#include <stdint.h>

namespace dvg {
namespace utils {

class Tile{
 public:
  Tile(){ path_ = ""; flags_ = 0; }
  Tile(const std::string &path, const char &flags)
      : path_(path), flags_(flags) {}
  virtual ~Tile(){}

  const std::string &get_path() const { return path_; }
  const uint8_t &get_flags() const { return flags_; }
    
  void set_path(const std::string &path) { path_ = path; }
  void set_flags(const uint8_t &flags) { flags_ = flags; }

 private:
  std::string path_;
  uint8_t flags_;
};

} // namespace utils 
} // namespace dvg


#endif
