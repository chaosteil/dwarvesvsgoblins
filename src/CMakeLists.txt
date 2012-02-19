include_directories(.)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/lib)

add_definitions(-Wall -Wextra -W -ggdb)

link_libraries()

add_executable(dvg
  main.cpp
)

install(TARGETS dvg DESTINATION bin)
