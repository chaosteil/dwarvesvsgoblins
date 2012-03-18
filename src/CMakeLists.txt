include_directories(.)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/lib)

add_definitions(-Wall -Wextra -W -ggdb)

include_directories(
  "/usr/include/OIS"
  "/usr/include/OGRE"
  "/usr/include/OGRE/Terrain"
  "/usr/include/OGRE/Paging"
)
link_libraries(
  OIS
  OgreTerrain
  OgrePaging
  OgreMain
  pthread
)

add_executable(dvg
  main.cpp

  fmw/app_state_manager.cpp
  fmw/ogre_framework.cpp
  map/map.cpp
  map/tile.cpp
)

install(TARGETS dvg DESTINATION bin)
