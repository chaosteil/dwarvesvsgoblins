#include "fmw_test/menu_state.h"

using namespace Ogre;

namespace dvg {

MenuState::MenuState() : quit_(false) {}

void MenuState::enter() {
  OgreFramework *of = OgreFramework::getSingletonPtr();
  of->log->logMessage("Entering MenuState..");

  scene_manager_ = of->root->createSceneManager(ST_GENERIC, "MenuSceneMgr");
  scene_manager_->setAmbientLight(ColourValue(0.7f, 0.7f, 0.7f));

  camera_ = scene_manager_->createCamera("MenuCam");
  camera_->setPosition(Vector3(0, 25, -50));
  camera_->lookAt(Vector3(0, 0, 0));
  camera_->setNearClipDistance(1);

  camera_->setAspectRatio(Real(of->viewport->getActualWidth()) /
                          Real(of->viewport->getActualHeight()));

  of->viewport->setCamera(camera_);

  of->tray_manager->destroyAllWidgets();
  of->tray_manager->showCursor();
  of->tray_manager->createButton(OgreBites::TL_CENTER, "EnterButton", "Enter GameState", 250);
  of->tray_manager->createButton(OgreBites::TL_CENTER, "ExitButton", "Exit Framework", 250);
  of->tray_manager->createLabel(OgreBites::TL_TOP, "MenuLbl", "Menu mode", 250);

  createScene();
}

void MenuState::createScene() {}

void MenuState::exit() {
  OgreFramework *of = OgreFramework::getSingletonPtr();
  of->log->logMessage("Leaving MenuState...");

  scene_manager_->destroyCamera(camera_);
  if (scene_manager_) {
    of->root->destroySceneManager(scene_manager_);
  }

  of->tray_manager->clearAllTrays();
  of->tray_manager->destroyAllWidgets();
  of->tray_manager->setListener(0);
}

bool MenuState::keyPressed(const OIS::KeyEvent &key_event) {
  OgreFramework *of = OgreFramework::getSingletonPtr();
  if (of->keyboard->isKeyDown(OIS::KC_ESCAPE)) {
    quit_ = true;
    return true;
  }

  of->keyPressed(key_event);
  return true;
}

bool MenuState::keyReleased(const OIS::KeyEvent &key_event) {
  OgreFramework::getSingletonPtr()->keyReleased(key_event);
  return true;
}

bool MenuState::mouseMoved(const OIS::MouseEvent &mouse_event) {
  if (OgreFramework::getSingletonPtr()->
      tray_manager->injectMouseMove(mouse_event)) {
    return true;
  }

  return true;
}

bool MenuState::mousePressed(const OIS::MouseEvent &mouse_event,
                             OIS::MouseButtonID id) {
  if (OgreFramework::getSingletonPtr()->
      tray_manager->injectMouseDown(mouse_event, id)) {
    return true;
  }

  return true;
}

bool MenuState::mouseReleased(const OIS::MouseEvent &mouse_event,
                              OIS::MouseButtonID id) {
  if (OgreFramework::getSingletonPtr()->
      tray_manager->injectMouseUp(mouse_event, id)) {
    return true;
  }

  return true;
}

void MenuState::buttonHit(OgreBites::Button *button) {
  if (button->getName() == "ExitButton") {
    quit_ = true;
  } else if (button->getName() == "EnterButton") {
    changeAppState(findByName("GameState"));
  }
}

void MenuState::update(double delta_time) {
  frame_event_.timeSinceLastFrame = delta_time;
  OgreFramework::getSingletonPtr()->
      tray_manager->frameRenderingQueued(frame_event_);

  if (quit_) {
    shutdown();
    return;
  }
}

}  // namespace dvg
