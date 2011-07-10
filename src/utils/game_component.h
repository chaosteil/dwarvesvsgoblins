#ifndef DVG_SRC_UTILS_GAME_COMPONENT_H_
#define DVG_SRC_UTILS_GAME_COMPONENT_H_

namespace dvg {
namespace utils {

class GameComponent {
 public:
  GameComponent(GameComponentManager *manager) : manager_(manager) {}
  virtual ~GameComponent() { manager_->Cleanup(this); }

  // TODO: Receive Message
 
 private:
  GameComponentManager *manager_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_GAME_COMPONENT_H_
