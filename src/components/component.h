#ifndef DWARVESVERSUSGOBLINS_SRC_COMPONENTS_COMPONENT_H_
#define DWARVESVERSUSGOBLINS_SRC_COMPONENTS_COMPONENT_H_

namespace dvg {

class Entity;
class Message;

class Component {
 public:
  virtual ~Component() {}
  virtual void Init(Entity &) {}
  virtual void SendMessage(Entity &, const Message &) {}

 protected:
  Component() {}
};

}  // namespace dvg

#endif  // DWARVESVERSUSGOBLINS_SRC_COMPONENTS_COMPONENT_H_
