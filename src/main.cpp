#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "dvg_config.h"
#include "game/units/imp_unit_logic.h"
#include "game/wall_tile.h"
#include "graphics/components/simple_render_component.h"
#include "graphics/resource_manager.h"
#include "utils/game_object.h"
#include "utils/scene_manager.h"
#include "graphics/components/map_render_component.h"
#include "game/components/map_logic_component.h"

using namespace dvg;

int main(int, const char **) {
  std::cout << "Dwarves vs. Goblins\nVersion: "
            << DVG_VERSION_STRING << std::endl;

  sf::VideoMode video_mode(800, 600, 32);
  sf::RenderWindow screen(video_mode, "Dwarves vs. Goblins", sf::Style::Close);
  sf::View view(sf::Vector2f(video_mode.Width / 2, video_mode.Height / 2),
                sf::Vector2f(video_mode.Width, video_mode.Height));

  screen.SetView(view);

  graphics::ResourceManager resource_manager;
  utils::SceneManager scene_manager;
  
  game::MapLogicComponent *map_logic_component = 
    new game::MapLogicComponent(utils::Vector2d(50, 50), scene_manager);
  graphics::MapRenderComponent *map_render_component = 
    new graphics::MapRenderComponent(*map_logic_component);
  utils::GameObject *map =
    new utils::GameObject(scene_manager,
                          NULL, map_logic_component, map_render_component, NULL,
                          utils::Rectangle(utils::Vector2d(0.0, 0.0),
                                           utils::Vector2d(0.0, 0.0)),
                          utils::Vector2d(0, 0), 0);
 
  graphics::SimpleRenderComponent *unit_render =
    new graphics::SimpleRenderComponent(
      resource_manager.GetTexture("tiles/testimp.png"));

  game::ImpUnitLogic *logic =
    new game::ImpUnitLogic();

  utils::GameObject *unit =
    new utils::GameObject(scene_manager,
                          new game::ImpUnitInput(*logic), logic, unit_render, NULL,
                          utils::Rectangle(utils::Vector2d(4.0, 4.0),
                                           utils::Vector2d(1.0, 1.0)),
                          utils::Vector2d(0, 0), 0);

  scene_manager.Attach(map);
  scene_manager.Attach(unit);

  sf::Event event;
  bool running = true;
  while (running) {
    screen.SetView(view);
    screen.Clear(sf::Color(0, 0, 0));
    
    while (screen.PollEvent(event)) {
      scene_manager.HandleInput(event);

      if (event.Type == sf::Event::Closed) {
        running = false;
      } else if (event.Type == sf::Event::KeyPressed) {
        if (event.Key.Code == sf::Keyboard::Escape) {
          running = false;
        } else if (event.Key.Code == sf::Keyboard::A) {
          view.Move(-5, 0);
        } else if (event.Key.Code == sf::Keyboard::D) {
          view.Move(5, 0);
        } else if (event.Key.Code == sf::Keyboard::W) {
          view.Move(0, -5);
        } else if (event.Key.Code == sf::Keyboard::S) {
          view.Move(0, 5);
        }
      } else if (event.Type == sf::Event::MouseWheelMoved) {
        float zoom = 1.0f;
        if (event.MouseWheel.Delta > 0)
          zoom = 1.1f;
        else if (event.MouseWheel.Delta < 0)
          zoom = 0.9f;
        view.Zoom(zoom);
      }
    }
    
    scene_manager.Update();
    scene_manager.Render(screen);
    screen.Display();
  }

  return 0;
}
