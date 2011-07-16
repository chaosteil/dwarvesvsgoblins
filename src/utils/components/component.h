#ifndef DVG_SRC_UTILS_COMPONENTS_COMPONENT_H_
#define DVG_SRC_UTILS_COMPONENTS_COMPONENT_H_

namespace dvg {
namespace utils {

class GameObject;
class Message;

class Component {
 public:
  virtual ~Component() {}
  virtual void Init(GameObject &) {}
  virtual void SendMessage(GameObject &, const Message &) {}

 protected:
  Component() {}
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_COMPONENTS_COMPONENT_H_
