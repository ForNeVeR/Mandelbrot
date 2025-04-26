# SPDX-FileCopyrightText: 2010-2025 Mandelbrot contributors <https://github.com/ForNeVeR/Mandelbrot>
#
# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 2.8)

##########
# project

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
  ${Boost_INCLUDE_DIRS}
  ${SDL2_INCLUDE_DIR}
)

##############
# application

add_executable(Mandelbrot
  src/main.cpp
  src/MandelDrawer.cpp
  src/MandelDrawer.calculate.cpp
  src/MandelThread.cpp
  src/MandelThread.work.cpp
  src/MandelMap.cpp
  src/text_rendering.cpp
)

target_link_libraries(Mandelbrot
  ${Boost_LIBRARIES}
  ${SDL2_LIBRARY}
)
