cmake_minimum_required(VERSION 3.0)

project(game_of_life)

file(GLOB_RECURSE SOURCES src/*.cpp include/*.h)
file(GLOB_RECURSE RESOURCES resources/fonts/*)

set(EXECUTABLE_NAME "game_of_life")
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${RESOURCES})

target_compile_options(${EXECUTABLE_NAME} PUBLIC -std=c++11 -Wall -g -O3)

file(COPY ${RESOURCES} DESTINATION resources/fonts)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2.3.2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

