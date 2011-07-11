#ifndef DVG_SRC_UTILS_COMPONENTS_RENDER_COMPONENT_H_
#define DVG_SRC_UTILS_COMPONENTS_RENDER_COMPONENT_H_

#include <list>
#include <boost/foreach.hpp>

namespace dvg {
namespace utils {

class GameObject;

class RenderComponent {
 public:
  virtual ~RenderComponent() {}
  virtual void Init(GameObject &) {}

  virtual void Render(GameObject &game_object) = 0;

 protected:
  RenderComponent() {}
};

class EmptyRenderComponent : public RenderComponent {
 public:
  EmptyRenderComponent() {}
  virtual ~EmptyRenderComponent() {}

  virtual void Render(GameObject &) {}
};

class CompositeRenderComponent : public RenderComponent {
 public:
  CompositeRenderComponent() {}
  virtual ~CompositeRenderComponent() {
    BOOST_FOREACH (RenderComponent *component, components_) {
      delete component;
    }
  }

  virtual void AddComponent(RenderComponent *component) {
    components_.push_back(component);
  }
  

  virtual void Render(GameObject &game_object) {
    BOOST_FOREACH (RenderComponent *component, components_) {
      component->Render(game_object);
    }
  }

 private:
  std::list<RenderComponent*> components_;
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_COMPONENTS_RENDER_COMPONENT_H_
