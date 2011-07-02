#ifndef DVG_SRC_GAME_TILE_H_
#define DVG_SRC_GAME_TILE_H_

namespace dvg {
namespace game {

class Tile {
 public:
  Tile(char data);
  virtual ~Tile();
  
  void set_data(char data) { data_ = data; }
  char data() const { return data_; }
 
 private:
  char data_;
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_TILE_H_
