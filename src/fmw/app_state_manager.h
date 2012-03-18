#ifndef DWARVESVSGOBLINS_SRC_FMW_APP_STATE_MANAGER_H_
#define DWARVESVSGOBLINS_SRC_FMW_APP_STATE_MANAGER_H_

#include "fmw/app_state.h"

namespace dvg {

class AppStateManager : public AppStateListener {
 public:
  struct StateInfo {
    std::string name;
    AppState *state;
  };

  AppStateManager();
  ~AppStateManager();

  void manageAppState(const std::string &name, AppState *state);

  AppState *findByName(const std::string &name);

  void start(AppState *state);
  void changeAppState(AppState *state);
  bool pushAppState(AppState *state);
  void popAppState();
  void pauseAppState();
  void shutdown();
  void popAllAndPushAppState(AppState *state);

 protected:
  void init(AppState *state);

  std::vector<AppState*> active_state_stack_;
  std::vector<StateInfo> states_;
  bool shutdown_;
};

}  // namespace dvg

#endif  // DWARVESVSGOBLINS_SRC_FMW_APP_STATE_MANAGER_H_
