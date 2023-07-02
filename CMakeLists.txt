cmake_minimum_required(VERSION 3.25)
project(Module_Test)

# NOTE: CMake can only generate module build files for Ninja and VS 2022 

# Is there a better way of doing this?
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.27") 
    message("CMake Version is greater than 3.27")
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
elseif(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.26") 
    message("CMake Version is greater than 3.26")
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
elseif(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.25")
    message("CMake Version is greater than 3.25")
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "3c375311-a3c9-4396-a187-3227ef642046")
endif()

# Enable MSVC Module support
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

# Must have at least c++20
set(CMAKE_CXX_STANDARD 20)

# Default to C++ extensions being off. Clang's modules support have trouble
# with extensions right now and it is not required for any other compiler
# How true is this still?
# set(CMAKE_CXX_EXTENSIONS OFF)

set(MODULE_DIR             "${CMAKE_CURRENT_SOURCE_DIR}/code/modules")
set(MODULE_BASIC_PLANE_DIR "${MODULE_DIR}/basic_plane")
set(MODULE_CSTD_DIR        "${MODULE_DIR}/cstd")

#
# C++ Standard Library Module
# NOTE: on MSVC, you can alternatively import the standard library as a module.
#

add_library(cstd STATIC)

target_sources(cstd
    PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS ${MODULE_CSTD_DIR}
        FILES
            ${MODULE_CSTD_DIR}/cstd.ixx
)

#
# Basic Plane Module
#

add_library(basic-plane STATIC)

target_sources(basic-plane
    PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS ${MODULE_BASIC_PLANE_DIR}
        FILES
            ${MODULE_BASIC_PLANE_DIR}/BasicPlane.Figures.ixx
            ${MODULE_BASIC_PLANE_DIR}/BasicPlane.Figures-Rectangle.ixx
            ${MODULE_BASIC_PLANE_DIR}/BasicPlane.Figures-Point.ixx
)

#
# Executable
#

add_executable(test-modules)

target_sources(
    test-modules
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/code/ModuleTest.cpp
)

target_link_libraries(test-modules PRIVATE basic-plane)
target_link_libraries(test-modules PRIVATE cstd)