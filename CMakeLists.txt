cmake_minimum_required(VERSION 3.20.4)

project(File-Watcher-Filter-CLI-Program CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(File-Watcher-Filter-CLI-Program ${SOURCES})
