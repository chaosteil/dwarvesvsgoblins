#include <iostream>

#include "fmw_test/demo_app.h"
#include "dvg_config.h"

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
// Windows platform

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

// Shows exception as message box
void show_exception(const std::exception &e) {
  MessageBoxA(NULL, e.what(), "An exception has occured!",
              MB_OK | MB_ICONERROR | MB_TASKMODAL);
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
// Some UNIX platform

// Shows exception in the console
void show_exception(const std::exception &e) {
  std::cerr << "An exception has occured: " << e.what() << std::endl;
}

int main(int /*argc*/, const char ** /*argv*/)
#endif
{
  dvg::DemoApp demo;
  try {
    demo.startDemo();
  } catch (std::exception &e) {
    show_exception(e);
  }
  return 0;
}
