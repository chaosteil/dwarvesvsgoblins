include_directories(.)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_definitions(-Wall -Wextra -W -ggdb)

# Includes the UnitTest++ library.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/UnitTest++/src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/UnitTest++)

add_executable(dvg_test
  main.cpp
)

add_executable(dvg_demo
  demo.cpp

  ../src/fmw/app_state_manager.cpp
  ../src/fmw/ogre_framework.cpp
  fmw_test/demo_app.cpp
  fmw_test/game_state.cpp
  fmw_test/menu_state.cpp
  fmw_test/pause_state.cpp
)

add_dependencies(dvg_test dvg)
add_dependencies(dvg_demo dvg)

target_link_libraries(dvg_test UnitTest++)
target_link_libraries(dvg_demo UnitTest++)

add_test(DVG dvg_test)
