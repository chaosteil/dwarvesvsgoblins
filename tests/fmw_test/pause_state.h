#ifndef DWARVESVSGOBLINS_SRC_FMW_PAUSE_STATE_H_
#define DWARVESVSGOBLINS_SRC_FMW_PAUSE_STATE_H_

#include "fmw/app_state.h"

namespace dvg {

class PauseState : public AppState {
 public:
  PauseState();
  
  DECLARE_APPSTATE_CLASS(PauseState);

  void enter();
  void createScene();
  void exit();

  bool keyPressed(const OIS::KeyEvent &key_event);
  bool keyReleased(const OIS::KeyEvent &key_event);

  bool mouseMoved(const OIS::MouseEvent &mouse_event);
  bool mousePressed(const OIS::MouseEvent &mouse_event,
                    OIS::MouseButtonID id);
  bool mouseReleased(const OIS::MouseEvent &mouse_event,
                     OIS::MouseButtonID id);

  void buttonHit(OgreBites::Button *button);
  void yesNoDialogClosed(const Ogre::DisplayString &question, bool yes_hit);

  void update(double delta_time);

 private:
  bool quit_;
  bool question_active_;
};

}  // namespace dvg

#endif  // DWARVESVSGOBLINS_SRC_FMW_PAUSE_STATE_H_
