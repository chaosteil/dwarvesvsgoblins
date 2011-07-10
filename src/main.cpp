#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "dvg_config.h"
#include "utils/position_component.h"
#include "utils/game_object.h"
#include "utils/default_component_manager.h"
#include "graphics/rendering_manager.h"
#include "graphics/resource_manager.h"

using namespace dvg;

int main(int, const char **) {
  std::cout << "Dwarves vs. Goblins\nVersion: "
            << DVG_VERSION_STRING << std::endl;

  sf::VideoMode video_mode(800, 600, 32);
  sf::RenderWindow screen(video_mode, "Dwarves vs. Goblins");
  sf::View view(sf::Vector2f(video_mode.Width / 2, video_mode.Height / 2),
                sf::Vector2f(video_mode.Width / 2, video_mode.Height / 2));
                
  screen.SetView(view);

  graphics::ResourceManager resource_manager;
  graphics::RenderingManager rendering_manager;
  
  std::vector<utils::GameObject *> tiles;
  
  std::string tile_texture_name;
  for (int y = 0; y < 50; y++) {
    for (int x = 0; x < 50; x++) {
      char tile_type = rand() % 2 + 1;
      
      if (tile_type == 1) {
        tile_texture_name = "tiles/dirt.png";
      } else if (tile_type == 2) {
        tile_texture_name = "tiles/grass.png";
      } else {
        tile_texture_name = "tiles/black.png";
      }
 
      utils::GameObject *tile = new utils::GameObject();
      rendering_manager.Register(*tile, 
                                 resource_manager.GetTexture(tile_texture_name), 
                                 sf::Vector2f(x * 32, y * 32));
      tiles.push_back(tile);
    }
  }
  
  sf::Event event;
  bool running = true;
  while (running) {
      screen.Clear(sf::Color(0, 0, 0));
      rendering_manager.Render(screen);
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
  
  for (uint32_t i = 0; i < tiles.size(); i++)
    delete tiles[i];

  return 0;
}
