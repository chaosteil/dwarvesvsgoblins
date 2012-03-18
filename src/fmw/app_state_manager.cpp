#include "fmw/app_state_manager.h"

#include <boost/foreach.hpp>
#include <OGRE/OgreWindowEventUtilities.h>

namespace dvg {

AppStateManager::AppStateManager()
  : shutdown_(false) {}

AppStateManager::~AppStateManager() {
  StateInfo si;

  while (!active_state_stack_.empty()) {
    active_state_stack_.back()->exit();
    active_state_stack_.pop_back();
  }

  while (!states_.empty()) {
    si = states_.back();
    si.state->destroy();
    states_.pop_back();
  }
}

void AppStateManager::manageAppState(const std::string &name,
                                     AppState *state) {
  try {
    StateInfo state_info;
    state_info.name = name;
    state_info.state = state;
    states_.push_back(state_info);
  } catch (std::exception &e) {
    delete state;
    throw Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR,
                          "Error while trying to manage a new AppState\n" +
                          Ogre::String(e.what()), "app_state_manager.cpp");
  }
}

AppState *AppStateManager::findByName(const std::string &name) {
  BOOST_FOREACH (StateInfo &info, states_) {
    if (info.name == name) {
      return info.state;
    }
  }

  return NULL;
}

void AppStateManager::start(AppState *state) {
  changeAppState(state);

  int delta_time = 1;
  int start_time = 0;

  while (!shutdown_) {
    OgreFramework *of = OgreFramework::getSingletonPtr();
    if (of->render_window->isClosed()) {
      shutdown_ = true;
    }

    Ogre::WindowEventUtilities::messagePump();
    
    if (of->render_window->isActive()) {
      start_time = of->timer->getMillisecondsCPU();

      of->keyboard->capture();
      of->mouse->capture();
      active_state_stack_.back()->update(delta_time);

      of->updateOgre(delta_time);
      of->root->renderOneFrame();

      delta_time = of->timer->getMillisecondsCPU() - start_time;
    } else {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
      Sleep(1000);
#else
      sleep(1);
#endif
    }
  }
  
  OgreFramework::getSingletonPtr()->log->logMessage("Main loop quit");
}

void AppStateManager::changeAppState(AppState *state) {
  if (!active_state_stack_.empty()) {
    active_state_stack_.back()->exit();
    active_state_stack_.pop_back();
  }

  active_state_stack_.push_back(state);
  init(state);
  active_state_stack_.back()->enter();
}

bool AppStateManager::pushAppState(AppState *state) {
  if (!active_state_stack_.empty()) {
    if (!active_state_stack_.back()->pause()) {
      return false;
    }
  }

  active_state_stack_.push_back(state);
  init(state);
  active_state_stack_.back()->enter();

  return true;
}

void AppStateManager::popAppState() {
  if (!active_state_stack_.empty()) {
    active_state_stack_.back()->exit();
    active_state_stack_.pop_back();
  }

  if (!active_state_stack_.empty()) {
    init(active_state_stack_.back());
    active_state_stack_.back()->resume();
  } else {
    shutdown();
  }
}

void AppStateManager::popAllAndPushAppState(AppState *state) {
  while (!active_state_stack_.empty()) {
    active_state_stack_.back()->exit();
    active_state_stack_.pop_back();
  }

  pushAppState(state);
}

void AppStateManager::pauseAppState() {
  if (!active_state_stack_.empty()) {
    active_state_stack_.back()->pause();
  }

  if (active_state_stack_.size() > 2) {
    init(active_state_stack_.at(active_state_stack_.size() - 2));
    active_state_stack_.at(active_state_stack_.size() - 2)->resume();
  }
}

void AppStateManager::shutdown() {
  shutdown_ = true;
}

void AppStateManager::init(AppState *state) {
  OgreFramework *of = OgreFramework::getSingletonPtr();
  of->keyboard->setEventCallback(state);
  of->mouse->setEventCallback(state);
  of->tray_manager->setListener(state);
  of->render_window->resetStatistics();
}

}  // namespace dvg
