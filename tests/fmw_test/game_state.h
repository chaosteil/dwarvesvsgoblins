#ifndef DWARVESVSGOBLINS_SRC_GAME_STATE_H_
#define DWARVESVSGOBLINS_SRC_GAME_STATE_H_

#include "fmw/app_state.h"

#include <OGRE/OgreSubEntity.h>
#include <OGRE/OgreMaterialManager.h>

namespace dvg {

enum QueryFlags {
  kOgreHeadMask = 1<<0,
  kCubeMask     = 1<<1
};

class GameState : public AppState {
 public:
  GameState();

  DECLARE_APPSTATE_CLASS(GameState);

  void enter();
  void createScene();
  void exit();
  bool pause();
  void resume();

  void moveCamera();
  void getInput();
  void buildGUI();

  bool keyPressed(const OIS::KeyEvent &key_event);
  bool keyReleased(const OIS::KeyEvent &key_event);

  bool mouseMoved(const OIS::MouseEvent &mouse_event);
  bool mousePressed(const OIS::MouseEvent &mouse_event, OIS::MouseButtonID id);
  bool mouseReleased(const OIS::MouseEvent &mouse_event,
                     OIS::MouseButtonID id);

  void onLeftPressed(const OIS::MouseEvent &mouse_event);
  void itemSelected(OgreBites::SelectMenu *menu);

  void update(double delta_time);

 private:
  Ogre::SceneNode *ogre_head_node_;
  Ogre::Entity *ogre_head_entity_;
  Ogre::MaterialPtr ogre_head_material_;
  Ogre::MaterialPtr ogre_head_material_high_;

  OgreBites::ParamsPanel *details_panel_;
  bool quit_;

  Ogre::Vector3 translate_vector_;
  Ogre::Real move_speed_;
  Ogre::Degree rotate_speed_;
  float move_scale_;
  Ogre::Degree rotate_scale_;

  Ogre::RaySceneQuery *ray_scene_query_;
  Ogre::SceneNode *current_object_;
  Ogre::Entity *current_entity_;
  bool left_mouse_down_;
  bool right_mouse_down_;
  bool settings_mode_;
};

}  // namespace dvg

#endif  // DWARVESVSGOBLINS_SRC_GAME_STATE_H_
