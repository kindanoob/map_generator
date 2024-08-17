cmake_minimum_required(VERSION 3.22.1)

project(map_generator)

file(GLOB_RECURSE SOURCES src/*.cpp include/*.h)
file(GLOB_RECURSE RESOURCES resources/fonts/*)

set(SFML_STATIC_LIBRARIES TRUE)

#Define path to your SFML root here (for example, C:/libs/SFML-2.6.1)
set(SFML_ROOT "path/to/your/SFML/root/folder")

set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
set(EXECUTABLE_NAME "map_generator")
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${RESOURCES})

target_compile_options(${EXECUTABLE_NAME} PUBLIC -std=c++14 -O3)

file(COPY ${RESOURCES} DESTINATION resources/fonts)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(SFML 2.5 REQUIRED network audio graphics window system)

target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-system)
