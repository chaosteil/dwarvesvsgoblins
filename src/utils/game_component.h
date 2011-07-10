#ifndef DVG_SRC_UTILS_GAME_COMPONENT_H_
#define DVG_SRC_UTILS_GAME_COMPONENT_H_

namespace dvg {
namespace utils {

class GameComponent {
 public:
  virtual ~GameComponent() {}

  // TODO: Receive Message

 protected:
  GameComponent() {}
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_GAME_COMPONENT_H_
