#ifndef DWARVESVSGOBLINS_SRC_FMW_APP_STATE_H_
#define DWARVESVSGOBLINS_SRC_FMW_APP_STATE_H_

#include "fmw/ogre_framework.h"

namespace dvg {

class AppState;

class AppStateListener {
 public:
  AppStateListener() {}
  virtual ~AppStateListener() {}

  virtual void manageAppState(const std::string &state_name,
                              AppState *state) = 0;

  virtual AppState *findByName(const std::string &state_name) = 0;
  virtual void changeAppState(AppState *state) = 0;
  virtual bool pushAppState(AppState *state) = 0;
  virtual void popAppState() = 0;
  virtual void pauseAppState() = 0;
  virtual void shutdown() = 0;
  virtual void popAllAndPushAppState(AppState *state) = 0;
};

class AppState
  : public OIS::KeyListener, public OIS::MouseListener,
    public OgreBites::SdkTrayListener {
 public:
  static void create(AppStateListener * /*parent*/,
                     const std::string & /*name*/) {}

  void destroy() { delete this; }

  virtual void enter() = 0;
  virtual void exit() = 0;
  virtual bool pause() { return true; }
  virtual void resume() {}
  virtual void update(double delta_time) = 0;

 protected:
  AppState() {}

  AppState *findByName(const std::string &state_name) {
    return parent_->findByName(state_name);
  }
  void changeAppState(AppState *state) {
    parent_->changeAppState(state);
  }
  bool pushAppState(AppState *state) {
    return parent_->pushAppState(state);
  }
  void popAppState() {
    parent_->popAppState();
  }
  void shutdown() {
    parent_->shutdown();
  }
  void popAllAndPushAppState(AppState *state) {
    parent_->popAllAndPushAppState(state);
  }

  AppStateListener *parent_;
  Ogre::Camera *camera_;
  Ogre::SceneManager *scene_manager_;
  Ogre::FrameEvent frame_event_;
};

#define DECLARE_APPSTATE_CLASS(T) \
    static void create(AppStateListener *parent, const std::string &name) { \
      T *app = new T(); \
      app->parent_ = parent; \
      parent->manageAppState(name, app); \
    } \

}  // namespace dvg

#endif  // DWARVESVSGOBLINS_SRC_FMW_APP_STATE_H_
