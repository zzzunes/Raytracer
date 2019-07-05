cmake_minimum_required(VERSION 3.13)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
	message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
	message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
		${CMAKE_CURRENT_BINARY_DIR}/googletest-build
		EXCLUDE_FROM_ALL)


project(Raytracer)
include_directories("src")
include_directories("tests")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wextra -Wall -Werror -pedantic -O0")
add_executable(Raytracer src/main.cc src/raytracer.cc src/raytracer.h src/geometry.h src/sphere.h src/sphere.cc src/material.h src/light.h)
add_executable(Tests tests/raytracertest.cc src/raytracer.cc src/raytracer.h src/geometry.h src/sphere.h src/sphere.cc)
target_link_libraries(Tests gtest gtest_main)