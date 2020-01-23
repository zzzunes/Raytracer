cmake_minimum_required(VERSION 3.10)

project(Raytracer)
include_directories("src")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wextra -Wall -Werror -pedantic -O0")
add_executable(Raytracer src/main.cc src/raytracer.cc src/raytracer.h src/geometry.h src/sphere.h src/sphere.cc src/material.h src/light.h src/ray.h src/intersection.h)