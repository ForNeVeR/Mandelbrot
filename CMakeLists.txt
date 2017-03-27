cmake_minimum_required(VERSION 2.8)

##########
# project
# TODO: Windos/VS features

project("Mandelbrot")

###########
# packages

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Boost 1.63 COMPONENTS thread)
find_package(SDL2)

if(NOT Boost_FOUND)
  message(FATAL_ERROR "Boost not found")
endif()

if(NOT SDL2_FOUND)
  message(FATAL_ERROR "SDL2 not found")
endif()

##########
# globals

include_directories(
  ${SDL_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
)

##############
# application

add_executable(Mandelbrot
  main.cpp
  MandelDrawer.cpp
  MandelThread.cpp
  MandelMap.cpp
  text_rendering.cpp
)

target_link_libraries(Mandelbrot
  ${SDL2_LIBRARY}
  ${Boost_LIBRARIES}
)
