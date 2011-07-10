include_directories(.)

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
  graphics/rendering_manager.cpp
  graphics/renderable_component.cpp

  utils/rectangle.cpp
  utils/quadtree.cpp
  utils/position_component.cpp
)

install(TARGETS dvg DESTINATION bin)
