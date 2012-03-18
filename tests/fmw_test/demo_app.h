#ifndef DWARVESVSGOBLINS_SRC_FMW_DEMO_APP_H_
#define DWARVESVSGOBLINS_SRC_FMW_DEMO_APP_H_

#include "fmw/ogre_framework.h"
#include "fmw/app_state_manager.h"

namespace dvg {

class DemoApp {
 public:
  DemoApp();
  ~DemoApp();

  void startDemo();

 private:
  AppStateManager *app_state_manager_;
};

}  // namespace dvg

#endif  // DWARVESVSGOBLINS_SRC_FMW_DEMO_APP_H_
