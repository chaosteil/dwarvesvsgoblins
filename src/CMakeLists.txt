include_directories(.)

include_directories(/usr/include/python2.7)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/lib)

add_definitions(-Wall -Wextra -W -ggdb)

link_libraries(
  boost_system
  boost_python
  python2.7
  sfml-system
  sfml-window
  sfml-graphics
)

add_executable(dvg
  main.cpp

  game/map_logic.cpp
  game/tiles/ground_tile.cpp
  game/tiles/tile.cpp
  game/tiles/wall_tile.cpp
  game/units/simple_unit_logic.cpp
  game/units/imp_unit_logic.cpp
  game/map.cpp
  game/map_logic.cpp
  
  graphics/resource_manager.cpp
  graphics/simple_renderer.cpp
  graphics/map_renderer.cpp

  utils/game_object.cpp
  utils/scene_manager.cpp
  utils/rectangle.cpp
  utils/quadtree.cpp
  utils/map_loader.cpp
  utils/map_data.cpp
  utils/tile_set_loader.cpp
  utils/tile_set_data.cpp
  utils/tile.h
)

add_library(dvg_external SHARED
  python/example.cpp
)

install(TARGETS dvg DESTINATION bin)
install(TARGETS dvg_external DESTINATION src/python)
