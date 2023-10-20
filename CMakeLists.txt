cmake_minimum_required(VERSION 3.22)
project(dir_comparison)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(main runner/runner.cpp src/directory.cpp src/file.cpp src/comparator_of_directories.cpp)
add_executable(a main.cpp)
