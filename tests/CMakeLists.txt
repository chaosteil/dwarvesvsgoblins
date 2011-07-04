include_directories(.)
include_directories(../src)

# Includes the UnitTest++ library.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/UnitTest++/src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/UnitTest++)

add_executable(dvg_test
  main.cpp

  vector2d.cpp
  quadtree.cpp
)

target_link_libraries(dvg_test UnitTest++)

add_test(DVG dvg_test)
