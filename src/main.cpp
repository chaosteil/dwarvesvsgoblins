#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "dvg_config.h"
#include "game/map.h"
#include "graphics/map_renderer.h"

using namespace dvg;

int main(int, const char **) {
  std::cout << "Dwarves vs. Goblins\nVersion: "
            << DVG_VERSION_STRING << std::endl;

  sf::VideoMode video_mode(800, 600, 32);
  sf::RenderWindow screen(video_mode, "Dwarves vs. Goblins");
  sf::View view(sf::Vector2f(video_mode.Width / 2, video_mode.Height / 2),
                sf::Vector2f(video_mode.Width / 2, video_mode.Height / 2));
                
  screen.SetView(view);

  game::Map test_map(utils::Vector2d(20, 20));
  graphics::MapRenderer test_map_renderer(test_map);
  
  sf::Event event;
  bool running = true;
  while (running) {
      screen.Clear(sf::Color(0, 0, 0));
      test_map_renderer.Render(screen);
      screen.Display();
      
      while (screen.GetEvent(event)) {
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
  }

  return 0;
}
