#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "game/map.h"
#include "graphics/map_renderer.h"
#include "dvg_config.h"

int main(int , const char **) {
  std::cout << "Dwarves vs. Goblins\nVersion: "
            << DVG_VERSION_STRING << std::endl;

  sf::RenderWindow screen(sf::VideoMode(800, 600, 32), "Dwarves vs. Goblins");
  dvg::game::Map test_map(20, 20);
  dvg::graphics::MapRenderer test_map_renderer(test_map);
  
  sf::Event event;
  bool running = true;
  while (running) {
      test_map_renderer.Render(screen);
      screen.Display();
      
      while (screen.GetEvent(event)) {
        if (event.Type == sf::Event::Closed)
          running = false;
        else if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)
          running = false;
      }
  }

  return 0;
}
