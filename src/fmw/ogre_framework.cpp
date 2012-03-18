#include "fmw/ogre_framework.h"

using namespace Ogre;

namespace dvg {

template<> OgreFramework *Ogre::Singleton<OgreFramework>::ms_Singleton = NULL;

OgreFramework::OgreFramework()
  : root(NULL), render_window(NULL), viewport(NULL), log(NULL), timer(NULL),
    input_manager(NULL), keyboard(NULL), mouse(NULL), tray_manager(NULL),
    show_stats_(false) {}

OgreFramework::~OgreFramework() {
  OgreFramework::getSingletonPtr()->log->logMessage("Shutting down OGRE...");

  delete tray_manager;
  if (input_manager) {
    OIS::InputManager::destroyInputSystem(input_manager);
  }
  delete root;
}

bool OgreFramework::initOgre(const std::string &title,
                             OIS::KeyListener *key_listener,
                             OIS::MouseListener *mouse_listener) {
  Ogre::LogManager *log_manager = new Ogre::LogManager();

  log = Ogre::LogManager::getSingleton().createLog("Logfile.txt", true, true,
                                                   false);
  log->setDebugOutputEnabled(true);

  root = new Ogre::Root();

  manualRenderInit();

  render_window = root->initialise(true, title);

  viewport = render_window->addViewport(0);
  viewport->setBackgroundColour(ColourValue(0.5f, 0.5f, 0.5f, 1.0f));
  viewport->setCamera(0);

  size_t window = 0;
  OIS::ParamList param_list;
  render_window->getCustomAttribute("WINDOW", &window);

  param_list.insert(
     OIS::ParamList::value_type("WINDOW",
                                Ogre::StringConverter::toString(window)));
  
  input_manager = OIS::InputManager::createInputSystem(param_list);
  keyboard = static_cast<OIS::Keyboard*>(
      input_manager->createInputObject(OIS::OISKeyboard, true));
  mouse = static_cast<OIS::Mouse*>(
      input_manager->createInputObject(OIS::OISMouse, true));

  mouse->getMouseState().height = render_window->getHeight();
  mouse->getMouseState().width = render_window->getWidth();

  if (key_listener == 0) {
    keyboard->setEventCallback(key_listener);
  } else {
    keyboard->setEventCallback(this);
  }

  if (mouse_listener) {
    mouse->setEventCallback(mouse_listener);
  } else {
    mouse->setEventCallback(this);
  }

  std::string sec_name, type_name, arch_name;
  Ogre::ConfigFile cf;
  cf.load("resources.cfg");

  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
  while (seci.hasMoreElements()) {
    sec_name = seci.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i) {
      type_name = i->first;
      arch_name = i->second;
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
          arch_name, type_name, sec_name);
    }
  }

  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  tray_manager = new OgreBites::SdkTrayManager("TestTrayMgr", render_window, 
                                               mouse, 0);
  tray_manager->hideLogo();

  timer = new Ogre::Timer();
  timer->reset();

  render_window->setActive(true);

  return true;
}

void OgreFramework::updateOgre(double /*delta_time*/) {
}

bool OgreFramework::keyPressed(const OIS::KeyEvent & /*key_event*/) {
  if (keyboard->isKeyDown(OIS::KC_SYSRQ)) {
    render_window->writeContentsToTimestampedFile("Test_Screenshot_", ".jpg");
    return true;
  }

  if (keyboard->isKeyDown(OIS::KC_L)) {
    if (show_stats_) {
      tray_manager->hideFrameStats();
    } else {
      tray_manager->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    }
    show_stats_ = !show_stats_;
  }

  return true;
}

bool OgreFramework::keyReleased(const OIS::KeyEvent & /*key_event*/) {
  return true;
}

bool OgreFramework::mouseMoved(const OIS::MouseEvent & /*mouse_event*/) {
  return true;
}

bool OgreFramework::mousePressed(const OIS::MouseEvent & /*mouse_event*/,
                                 OIS::MouseButtonID /*id*/) {
  return true;
}

bool OgreFramework::mouseReleased(const OIS::MouseEvent & /*mouse_event*/,
                                  OIS::MouseButtonID /*id*/) {
  return true;
}

void OgreFramework::manualRenderInit() {
  const RenderSystemList &renderers = Root::getSingleton().getAvailableRenderers();

  if (renderers.empty()) {
    return;
  }

  RenderSystem *renderer = *renderers.begin();
  Root::getSingleton().setRenderSystem(renderer);

  renderer->setConfigOption("Video Mode", " 640 x  480");
  renderer->setConfigOption("Full Screen", "No");
}

}  // namespace dvg
