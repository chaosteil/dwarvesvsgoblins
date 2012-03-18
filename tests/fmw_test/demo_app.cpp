#include "fmw_test/demo_app.h"

#include "fmw_test/menu_state.h"
#include "fmw_test/game_state.h"
#include "fmw_test/pause_state.h"

namespace dvg {

DemoApp::DemoApp() : app_state_manager_(NULL) {}

DemoApp::~DemoApp() {
  delete app_state_manager_;
  delete OgreFramework::getSingletonPtr();
}

void DemoApp::startDemo() {
  new OgreFramework();
  if (!OgreFramework::getSingletonPtr()->initOgre("OgreFramework", 0, 0)) {
    return;
  }

  OgreFramework::getSingletonPtr()->log->logMessage("Demo initialized!");

  app_state_manager_ = new AppStateManager();

  MenuState::create(app_state_manager_, "MenuState");
  GameState::create(app_state_manager_, "GameState");
  PauseState::create(app_state_manager_, "PauseState");

  app_state_manager_->start(app_state_manager_->findByName("MenuState"));
}

}  // namespace dvg
