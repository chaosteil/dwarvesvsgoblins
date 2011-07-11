include_directories(.)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs)

add_definitions(-Wall -Wextra -W -ggdb)

link_libraries(
  boost_system
  sfml-system
  sfml-window
  sfml-graphics
)

add_executable(dvg
  main.cpp
  
  graphics/resource_manager.cpp
  graphics/simple_render_component.cpp

  utils/game_object.cpp
  utils/scene_manager.cpp
  utils/rectangle.cpp
  utils/quadtree.cpp
  utils/position_component.cpp
)

install(TARGETS dvg DESTINATION bin)
