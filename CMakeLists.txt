cmake_minimum_required(VERSION 2.4)

##########
# project
# TODO: Windos/VS features

project("Mandelbrot")

###########
# packages

find_package(SDL)
find_package(Boost 1.37 COMPONENTS thread)

if(NOT SDL_FOUND)
  message(FATAL_ERROR "SDL not found")
endif()

if(NOT Boost_FOUND)
  message(FATAL_ERROR "Boost not found")
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
  text_rendering.cpp
)

target_link_libraries(Mandelbrot
  ${SDL_LIBRARY}
  ${Boost_LIBRARIES}
)