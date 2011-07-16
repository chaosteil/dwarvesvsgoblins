#ifndef DVG_SRC_GAME_MAP_H_
#define DVG_SRC_GAME_MAP_H_

#include "game/tile.h"
#include "utils/components/logic_component.h"
#include "utils/vector2d.h"

namespace dvg {
namespace game {

class Map : public utils::LogicComponent {
 public:
  Map(const utils::Vector2d &size);
  virtual ~Map();

  int width() const { return size_.x(); }
  int height() const { return size_.y(); }

  void set_data(const utils::Vector2d &pos, char data) {
    if (!OnMap(pos)) {
      return;
    }

    data_[TranslateTile(pos)]->set_data(data);
  }
  const Tile &data(const utils::Vector2d &pos) const {
    if (!OnMap(pos)) {
      return null_;
    }

    return *data_[TranslateTile(pos)];
  }

 private:
  int TranslateTile(const utils::Vector2d &pos) const {
    return pos.x() + pos.y() * size_.x();
  }

  bool OnMap(const utils::Vector2d &pos) const {
    if (pos.x() < 0 || pos.x() >= size_.x() ||
        pos.y() < 0 || pos.y() >= size_.y()) {
      return false;
    }

    return true;
  }

  utils::Vector2d size_;

  Tile null_;

  Tile **data_;
};

}  // namespace game
}  // namespace dvg

#endif  // DVG_SRC_GAME_MAP_H_
