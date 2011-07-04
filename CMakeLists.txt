cmake_minimum_required(VERSION 2.6)

#
# Dwarves vs Goblins
#
project(DVG)

# Set some version numbers
set(DVG_VERSION_MAJOR 0)
set(DVG_VERSION_MINOR 1)
set(DVG_VERSION_STATUS "pre")

# Define configure files
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/src/dvg_config.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/dvg_config.h"
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src bin)

enable_testing()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
