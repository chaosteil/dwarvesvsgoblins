include_directories(.)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_definitions(-Wall -Wextra -W -ggdb)

# Includes the UnitTest++ library.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/UnitTest++/src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/UnitTest++)

add_executable(dvg_test
  main.cpp

  message.cpp
  vector2d.cpp
  quadtree.cpp
  rectangle.cpp

  ../src/utils/rectangle.cpp
)

add_dependencies(dvg_test dvg)

target_link_libraries(dvg_test UnitTest++)

add_test(DVG dvg_test)
