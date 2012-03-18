#ifndef DWARVESVSGOBLINS_SRC_FMW_OGRE_FRAMEWORK_H_
#define DWARVESVSGOBLINS_SRC_FMW_OGRE_FRAMEWORK_H_

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreLogManager.h>
#include <OGRE/OgreOverlay.h>
#include <OGRE/OgreOverlayElement.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreViewport.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreConfigFile.h>

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include <OGRE/SdkTrays.h>

namespace dvg {

class OgreFramework : public Ogre::Singleton<OgreFramework>, OIS::KeyListener,
    OIS::MouseListener {
 public:
  OgreFramework();
  virtual ~OgreFramework();

  bool initOgre(const std::string &title,
                OIS::KeyListener *key_listener = NULL,
                OIS::MouseListener *mouse_listener = NULL);
  void updateOgre(double delta_time);

  bool keyPressed(const OIS::KeyEvent &key_event);
  bool keyReleased(const OIS::KeyEvent &key_event);

  bool mouseMoved(const OIS::MouseEvent &mouse_event);
  bool mousePressed(const OIS::MouseEvent &mouse_event, OIS::MouseButtonID id);
  bool mouseReleased(const OIS::MouseEvent &mouse_event,
                     OIS::MouseButtonID id);

  Ogre::Root *root;
  Ogre::RenderWindow *render_window;
  Ogre::Viewport *viewport;
  Ogre::Log *log;
  Ogre::Timer *timer;

  OIS::InputManager *input_manager;
  OIS::Keyboard *keyboard;
  OIS::Mouse *mouse;

  OgreBites::SdkTrayManager *tray_manager;

 private:
  OgreFramework(const OgreFramework &);
  OgreFramework& operator=(const OgreFramework &);

  void manualRenderInit();

  bool show_stats_;
};

}  // namespace dvg

#endif  // DWARVESVSGOBLINS_SRC_FMW_OGRE_FRAMEWORK_H_
