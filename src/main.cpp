#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "dvg_config.h"
#include "game/units/simple_unit_logic.h"
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
  sf::RenderWindow screen(video_mode, "Dwarves vs. Goblins", sf::Style::Close, 
			  sf::WindowSettings (32, 8, 0));
  sf::View view(sf::Vector2f(video_mode.Width / 2, video_mode.Height / 2),
                sf::Vector2f(video_mode.Width / 2, video_mode.Height / 2));
                
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
      resource_manager.GetTexture("tiles/grass.png"));
  utils::GameObject *unit =
    new utils::GameObject(scene_manager,
                          NULL, new game::SimpleUnitLogic(), unit_render, NULL,
                          utils::Rectangle(utils::Vector2d(4.0, 4.0),
                                           utils::Vector2d(1.0, 1.0)),
                          utils::Vector2d(0, 0), 0);

  scene_manager.Attach(map);
  scene_manager.Attach(unit);

  sf::Event event;
  const sf::Input &input = screen.GetInput();
  bool running = true;
  while (running) {
      screen.Clear(sf::Color(0, 0, 0));
      
      while (screen.GetEvent(event)) {
        scene_manager.HandleInputEvent(event);

        if (event.Type == sf::Event::Closed) {
          running = false;
        } else if (event.Type == sf::Event::KeyPressed) {
          if (event.Key.Code == sf::Key::Escape) {
            running = false;
          } else if (event.Key.Code == sf::Key::A) {
            view.Move(-5, 0);
          } else if (event.Key.Code == sf::Key::D) {
            view.Move(5, 0);
          } else if (event.Key.Code == sf::Key::W) {
            view.Move(0, -5);
          } else if (event.Key.Code == sf::Key::S) {
            view.Move(0, 5);
          }
        }
      }

      scene_manager.HandleInput(input);
      scene_manager.Update();
      scene_manager.Render(screen);
      screen.Display();
  }

  return 0;
}
