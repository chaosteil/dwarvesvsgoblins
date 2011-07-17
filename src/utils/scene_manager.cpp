#include "utils/scene_manager.h"

#include "utils/game_object.h"

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

void SceneManager::Render(sf::RenderWindow &window) {
  BOOST_FOREACH (GameObject *object, objects_) {
    object->Render(window);
  }
}

void SceneManager::HandleInput(const sf::Event &event) {
  BOOST_FOREACH (GameObject *object, objects_) {
    object->HandleInput(event);
  }
}
  
}  // namespace utils
}  // namespace dvg
