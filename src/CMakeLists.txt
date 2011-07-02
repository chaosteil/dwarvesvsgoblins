include_directories(.)

add_definitions(-Wall -Wextra -W -ggdb)

link_libraries(
  boost_system
  sfml-system
  sfml-window
  sfml-graphics
)

add_executable(dvg
  main.cpp)

install(TARGETS dvg DESTINATION bin)
