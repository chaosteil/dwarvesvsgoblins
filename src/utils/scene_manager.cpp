#include "utils/scene_manager.h"

#include "utils/components/game_object.h"

#include <boost/foreach.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace dvg {
namespace utils {
  
SceneManager::SceneManager() {
  
}

SceneManager::~SceneManager() {
  BOOST_FOREACH (GameObject *object, objects_) {
    delete object;
  }
}

void SceneManager::Attach(GameObject *object) {
  objects_.push_back(object);
}

void SceneManager::Update() {
  BOOST_FOREACH (GameObject *object, objects_) {
    object->Update();
  }
}

void SceneManager::Render() {
  BOOST_FOREACH (GameObject *object, objects_) {
    object->Render();
  }
}

void SceneManager::HandleInput() {
  BOOST_FOREACH (GameObject *object, objects_) {
    object->HandleInput();
  }
}
  
}  // namespace utils
}  // namespace dvg