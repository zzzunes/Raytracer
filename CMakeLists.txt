cmake_minimum_required(VERSION 3.13)
project(Raytracer)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "-Wextra -Wall -Werror -pedantic")
add_executable(Raytracer src/main.cc)