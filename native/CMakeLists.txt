cmake_minimum_required(VERSION 3.9)

project(test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

include_directories(include lib)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
