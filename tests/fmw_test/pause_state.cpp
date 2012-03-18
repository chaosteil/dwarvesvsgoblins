#include "fmw_test/pause_state.h"

using namespace Ogre;

namespace dvg {

PauseState::PauseState()
  : quit_(false), question_active_(false) {}

void PauseState::enter() {
  OgreFramework *of = OgreFramework::getSingletonPtr();
  of->log->logMessage("Entering PauseState...");

  scene_manager_ = of->root->createSceneManager(ST_GENERIC, "PauseSceneManager");
  scene_manager_->setAmbientLight(ColourValue(0.7f, 0.7f, 0.7f));

  camera_ = scene_manager_->createCamera("PauseCamera");
  camera_->setPosition(Vector3(0, 25, -50));
  camera_->lookAt(Vector3(0, 0, 0));
  camera_->setNearClipDistance(1);

  camera_->setAspectRatio(Real(of->viewport->getActualWidth())/
                          Real(of->viewport->getActualHeight()));

  of->viewport->setCamera(camera_);

  of->tray_manager->destroyAllWidgets();
  of->tray_manager->showCursor();
  of->tray_manager->createButton(OgreBites::TL_CENTER, "BackToGameButton", "Return to GameState", 250);
  of->tray_manager->createButton(OgreBites::TL_CENTER, "BackToMenuButton", "Return to Menu", 250);
  of->tray_manager->createButton(OgreBites::TL_CENTER, "ExitButton", "Exit", 250);
  of->tray_manager->createLabel(OgreBites::TL_TOP, "PauseLabel", "Pause mode", 250);

  quit_ = false;

  createScene();
}

void PauseState::createScene() {}

void PauseState::exit() {
  OgreFramework *of = OgreFramework::getSingletonPtr();
  of->log->logMessage("Leaving PauseState...");

  scene_manager_->destroyCamera(camera_);
  of->root->destroySceneManager(scene_manager_);

  of->tray_manager->clearAllTrays();
  of->tray_manager->destroyAllWidgets();
  of->tray_manager->setListener(0);
}

bool PauseState::keyPressed(const OIS::KeyEvent &key_event) {
  OgreFramework *of = OgreFramework::getSingletonPtr();

  if (of->keyboard->isKeyDown(OIS::KC_ESCAPE) && !question_active_) {
    quit_ = true;
    return true;
  }

  of->keyPressed(key_event);

  return true;
}

bool PauseState::keyReleased(const OIS::KeyEvent &key_event) {
  OgreFramework *of = OgreFramework::getSingletonPtr();

  of->keyReleased(key_event);

  return true;
}

bool PauseState::mouseMoved(const OIS::MouseEvent &mouse_event) {
  OgreFramework *of = OgreFramework::getSingletonPtr();

  if (of->tray_manager->injectMouseMove(mouse_event)) {
    return true;
  }

  return true;
}

bool PauseState::mousePressed(const OIS::MouseEvent &mouse_event,
                              OIS::MouseButtonID id) {
  OgreFramework *of = OgreFramework::getSingletonPtr();

  if (of->tray_manager->injectMouseDown(mouse_event, id)) {
    return true;
  }

  return true;
}

bool PauseState::mouseReleased(const OIS::MouseEvent &mouse_event,
                              OIS::MouseButtonID id) {
  OgreFramework *of = OgreFramework::getSingletonPtr();

  if (of->tray_manager->injectMouseUp(mouse_event, id)) {
    return true;
  }

  return true;
}

void PauseState::yesNoDialogClosed(const Ogre::DisplayString &question,
                                   bool yes_hit) {
  if (yes_hit) {
    shutdown();
  } else {
    OgreFramework::getSingletonPtr()->tray_manager->closeDialog();
  }

  question_active_ = false;
}

void PauseState::update(double delta_time) {
  frame_event_.timeSinceLastFrame = delta_time;
  OgreFramework::getSingletonPtr()->
      tray_manager->frameRenderingQueued(frame_event_);

  if (quit_) {
    popAppState();
    return;
  }
}

void PauseState::buttonHit(OgreBites::Button *button) {
  if (button->getName() == "ExitButton") {
    OgreFramework::getSingletonPtr()->tray_manager->showYesNoDialog("Sure?", "Really leave?");
    question_active_ = true;
  } else if (button->getName() == "BackToGameButton") {
    quit_ = true;
  } else if (button->getName() == "BackToMenuButton") {
    popAllAndPushAppState(findByName("MenuState"));
  }
}

}  // namespace dvg
