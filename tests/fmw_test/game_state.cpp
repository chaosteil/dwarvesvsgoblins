#include "fmw_test/game_state.h"

#include <boost/foreach.hpp>

using namespace Ogre;

namespace dvg {

GameState::GameState()
  : details_panel_(NULL),
    quit_(false), move_speed_(0.1f), rotate_speed_(0.3f),
    left_mouse_down_(false), right_mouse_down_(false),
    settings_mode_(false) {}

void GameState::enter() {
  OgreFramework *of = OgreFramework::getSingletonPtr();
  of->log->logMessage("Entering GameState...");

  scene_manager_ = of->root->createSceneManager(ST_GENERIC,
                                                "GameSceneManager");
  scene_manager_->setAmbientLight(ColourValue(0.7f, 0.7f, 0.7f));

  ray_scene_query_ = scene_manager_->createRayQuery(Ray());
  ray_scene_query_->setQueryMask(kOgreHeadMask);

  camera_ = scene_manager_->createCamera("GameCamera");
  camera_->setPosition(Vector3(5, 60, 60));
  camera_->lookAt(Vector3(5, 20, 0));
  camera_->setNearClipDistance(5);

  camera_->setAspectRatio(Real(of->viewport->getActualWidth())/
                          Real(of->viewport->getActualHeight()));

  of->viewport->setCamera(camera_);
  current_object_ = NULL;

  buildGUI();

  createScene();
}

void GameState::createScene() {
  scene_manager_->createLight("Light")->setPosition(75, 75, 75);

  ogre_head_entity_ = scene_manager_->createEntity("Cube", "ogrehead.mesh");
  ogre_head_entity_->setQueryFlags(kOgreHeadMask);
  ogre_head_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode("CubeNode");
  ogre_head_node_->attachObject(ogre_head_entity_);
  ogre_head_node_->setPosition(Vector3(0, 0, -25));

  ogre_head_material_ = ogre_head_entity_->getSubEntity(1)->getMaterial();
  ogre_head_material_high_ = ogre_head_material_->clone("OgreHeadMatHigh");
  ogre_head_material_high_->getTechnique(0)->getPass(0)->setAmbient(1, 0, 0);
  ogre_head_material_high_->getTechnique(0)->getPass(0)->setDiffuse(1, 0, 0, 0);
  
}

bool GameState::pause() {
  OgreFramework::getSingletonPtr()->log->logMessage("Pausing GameState...");

  return true;
}

void GameState::resume() {
  OgreFramework *of = OgreFramework::getSingletonPtr();

  of->log->logMessage("Resuming GameState...");

  buildGUI();

  of->viewport->setCamera(camera_);
  quit_ = false;
}

void GameState::exit() {
  OgreFramework *of = OgreFramework::getSingletonPtr();

  scene_manager_->destroyCamera(camera_);
  scene_manager_->destroyQuery(ray_scene_query_);

  of->root->destroySceneManager(scene_manager_);
}

bool GameState::keyPressed(const OIS::KeyEvent &key_event) {
  OgreFramework *of = OgreFramework::getSingletonPtr();
  if (settings_mode_) {
    if (of->keyboard->isKeyDown(OIS::KC_S)) {
      OgreBites::SelectMenu *menu =
          (OgreBites::SelectMenu*)of->tray_manager->
          getWidget("ChatModeSelMenu");
      if (menu->getSelectionIndex() + 1 < (int)menu->getNumItems()) {
        menu->selectItem(menu->getSelectionIndex() + 1);
      }
    }

    if (of->keyboard->isKeyDown(OIS::KC_S)) {
      OgreBites::SelectMenu *menu =
          (OgreBites::SelectMenu*)of->tray_manager->
          getWidget("ChatModeSelMenu");
      if (menu->getSelectionIndex() - 1 >= 0) {
        menu->selectItem(menu->getSelectionIndex() - 1);
      }
    }
  }
  
  if (of->keyboard->isKeyDown(OIS::KC_ESCAPE)) {
    pushAppState(findByName("PauseState"));
    return true;
  }

  if (of->keyboard->isKeyDown(OIS::KC_I)) {
    if (details_panel_->getTrayLocation() == OgreBites::TL_NONE) {
      of->tray_manager->moveWidgetToTray(details_panel_,
                                         OgreBites::TL_TOPLEFT, 0);
      details_panel_->show();
    } else {
      of->tray_manager->removeWidgetFromTray(details_panel_);
      details_panel_->hide();
    }
  }

  if (of->keyboard->isKeyDown(OIS::KC_TAB)) {
    settings_mode_ = !settings_mode_;
    return true;
  }

  if (settings_mode_ && (of->keyboard->isKeyDown(OIS::KC_RETURN) ||
      of->keyboard->isKeyDown(OIS::KC_NUMPADENTER))) {}

  if (!settings_mode_ || (settings_mode_ && !of->keyboard->isKeyDown(OIS::KC_L))) {
    of->keyPressed(key_event);
  }

  return true;
}

bool GameState::keyReleased(const OIS::KeyEvent &key_event) {
  OgreFramework::getSingletonPtr()->keyPressed(key_event);
  return true;
}

bool GameState::mouseMoved(const OIS::MouseEvent &mouse_event) {
  if (OgreFramework::getSingletonPtr()->tray_manager->injectMouseMove(mouse_event)) {
    return true;
  }

  if (right_mouse_down_) {
    camera_->yaw(Degree(mouse_event.state.X.rel * -0.1f));
    camera_->pitch(Degree(mouse_event.state.Y.rel * -0.1f));
  }

  return true;
}

bool GameState::mousePressed(const OIS::MouseEvent &mouse_event,
                             OIS::MouseButtonID id) {
  if (OgreFramework::getSingletonPtr()->tray_manager->injectMouseDown(mouse_event, id)) {
    return true;
  }

  if (id == OIS::MB_Left) {
    onLeftPressed(mouse_event);
    left_mouse_down_ = true;
  } else if (id == OIS::MB_Right) {
    right_mouse_down_ = true;
  }

  return true;
}

bool GameState::mouseReleased(const OIS::MouseEvent &mouse_event,
                              OIS::MouseButtonID id) {
  if (OgreFramework::getSingletonPtr()->tray_manager->injectMouseUp(mouse_event, id)) {
    return true;
  }

  if (id == OIS::MB_Left) {
    left_mouse_down_ = false;
  } else if (id == OIS::MB_Right) {
    right_mouse_down_ = false;
  }

  return true;
}

void GameState::onLeftPressed(const OIS::MouseEvent &mouse_event) {
  OgreFramework *of = OgreFramework::getSingletonPtr();

  if (current_object_) {
    current_object_->showBoundingBox(false);
    current_entity_->getSubEntity(1)->setMaterial(ogre_head_material_);
  }

  Ogre::Ray mouse_ray = camera_->getCameraToViewportRay(of->mouse->getMouseState().X.abs / float(mouse_event.state.width),
                                                        of->mouse->getMouseState().Y.abs / float(mouse_event.state.height));
  ray_scene_query_->setRay(mouse_ray);
  ray_scene_query_->setSortByDistance(true);

  Ogre::RaySceneQueryResult &result = ray_scene_query_->execute();
  BOOST_FOREACH (Ogre::RaySceneQueryResultEntry &ray, result) {
    if (ray.movable) {
      of->log->logMessage("MovableName: " + ray.movable->getName());
      current_object_ = scene_manager_->getEntity(ray.movable->getName())->getParentSceneNode();
      of->log->logMessage("ObjName " + current_object_->getName());
      current_object_->showBoundingBox(true);
      current_entity_ = scene_manager_->getEntity(ray.movable->getName());
      current_entity_->getSubEntity(1)->setMaterial(ogre_head_material_high_);
      break;
    }
  }
}

void GameState::moveCamera() {
  if (OgreFramework::getSingletonPtr()->keyboard->isKeyDown(OIS::KC_LSHIFT)) {
    camera_->moveRelative(translate_vector_);
  }

  camera_->moveRelative(translate_vector_ / 10);
}

void GameState::getInput() {
  OgreFramework *of = OgreFramework::getSingletonPtr();

  if (!settings_mode_) {
    if (of->keyboard->isKeyDown(OIS::KC_A)) {
      translate_vector_.x = -move_scale_;
    }

    if (of->keyboard->isKeyDown(OIS::KC_D)) {
      translate_vector_.x = move_scale_;
    }

    if (of->keyboard->isKeyDown(OIS::KC_W)) {
      translate_vector_.z = -move_scale_;
    }

    if (of->keyboard->isKeyDown(OIS::KC_S)) {
      translate_vector_.z = move_scale_;
    }
  }
}

void GameState::buildGUI() {
  OgreFramework *of = OgreFramework::getSingletonPtr();

  of->tray_manager->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  of->tray_manager->createLabel(OgreBites::TL_TOP, "GameLabel", "Game mode", 250);
  of->tray_manager->showCursor();

  Ogre::StringVector items;
  items.push_back("cam.pX");
  items.push_back("cam.pY");
  items.push_back("cam.pZ");
  items.push_back("cam.oW");
  items.push_back("cam.oX");
  items.push_back("cam.oY");
  items.push_back("cam.oZ");
  items.push_back("Mode");

  details_panel_ = of->tray_manager->createParamsPanel(OgreBites::TL_TOPLEFT,
                                                       "DetailsPanel", 200,
                                                       items);
  details_panel_->show();

  Ogre::String info_text = "[TAB] - Switch input mode\n\n[W] - Forward / Mode up\n[S] - Backwards / Mode down\n[A] - Left\n";
  info_text.append("[D] - Right \n\nPress [SHIFT] to move faster\n\n[L] - Toggle FPS / logo\n");
  info_text.append("[Print] - Take screenshot\n\n[ESC] - Exit");
  of->tray_manager->createTextBox(OgreBites::TL_RIGHT, "InfoPanel", info_text, 300, 220);

  Ogre::StringVector chat_modes;
  chat_modes.push_back("Solid mode");
  chat_modes.push_back("Wireframe mode");
  chat_modes.push_back("Point mode");
  of->tray_manager->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "ChatModeSelectMenu",
                                         "ChatMode", 200, 3, chat_modes);
}

void GameState::update(double delta_time) {
  OgreFramework *of = OgreFramework::getSingletonPtr();
  frame_event_.timeSinceLastFrame = delta_time;
  of->tray_manager->frameRenderingQueued(frame_event_);
  
  if (quit_) {
    popAppState();
    return;
  }

  if (of->tray_manager->isDialogVisible()) {
    if (details_panel_->isVisible()) {
      details_panel_->setParamValue(0, Ogre::StringConverter::toString(camera_->getDerivedPosition().x));
      details_panel_->setParamValue(1, Ogre::StringConverter::toString(camera_->getDerivedPosition().y));
      details_panel_->setParamValue(2, Ogre::StringConverter::toString(camera_->getDerivedPosition().z));
      details_panel_->setParamValue(3, Ogre::StringConverter::toString(camera_->getDerivedOrientation().w));
      details_panel_->setParamValue(4, Ogre::StringConverter::toString(camera_->getDerivedOrientation().x));
      details_panel_->setParamValue(5, Ogre::StringConverter::toString(camera_->getDerivedOrientation().y));
      details_panel_->setParamValue(6, Ogre::StringConverter::toString(camera_->getDerivedOrientation().z));

      details_panel_->setParamValue(7, settings_mode_ ? "Buffered Input" : "Un-Buffered Input");
    }
  }

  move_scale_ = move_speed_ * delta_time;
  rotate_scale_ = rotate_speed_ * delta_time;

  translate_vector_ = Vector3::ZERO;

  getInput();
  moveCamera();
}

void GameState::itemSelected(OgreBites::SelectMenu *menu) {
  switch (menu->getSelectionIndex()) {
    case 0: camera_->setPolygonMode(Ogre::PM_SOLID); break;
    case 1: camera_->setPolygonMode(Ogre::PM_WIREFRAME); break;
    case 2: camera_->setPolygonMode(Ogre::PM_POINTS); break;
  }
}

}  // namespace dvg
