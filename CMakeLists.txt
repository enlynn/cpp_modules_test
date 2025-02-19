cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

# NOTE: CMake can only generate module build files for Ninja and VS 2022 
if("${CMAKE_GENERATOR}" STREQUAL "Visual Studio 17 2022")
    # This can be done before or after project() on MSVC
    # It works regardless of CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
    set(CMAKE_CXX_SCAN_FOR_MODULES ON)
else()
    # This needs to be done before selecting the languages so the project() command
    # The CMAKE_EXPERIMENTAL_CXX_IMPORT_STD is required
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
    set(CMAKE_CXX_MODULE_STD ON)
endif()

# Is there a better way of doing this?
# if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.27") 
#     message("CMake Version is greater than 3.27")
#     set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
# elseif(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.26") 
#     message("CMake Version is greater than 3.26")
#     set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
# elseif(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.25")
#     message("CMake Version is greater than 3.25")
#     set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "3c375311-a3c9-4396-a187-3227ef642046")
# endif()

project(Module_Test)

# Enable MSVC Module support
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
# Currently CMake requires extensions enabled when using import std.
# https://gitlab.kitware.com/cmake/cmake/-/issues/25916
# https://gitlab.kitware.com/cmake/cmake/-/issues/25539
set(CMAKE_CXX_EXTENSIONS ON)

# Default to C++ extensions being off. Clang's modules support have trouble
# with extensions right now and it is not required for any other compiler
# How true is this still?
# set(CMAKE_CXX_EXTENSIONS OFF)

set(MODULE_DIR             "${CMAKE_CURRENT_SOURCE_DIR}/code/modules")
set(MODULE_BASIC_PLANE_DIR "${MODULE_DIR}/basic_plane")


add_executable(test-modules)

target_sources(
    test-modules
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/code/ModuleTest.cpp
)

target_sources(test-modules
    PRIVATE
        FILE_SET CXX_MODULES FILES
            ${MODULE_BASIC_PLANE_DIR}/BasicPlane.Figures.ixx
            ${MODULE_BASIC_PLANE_DIR}/BasicPlane.Figures-Rectangle.ixx
            ${MODULE_BASIC_PLANE_DIR}/BasicPlane.Figures-Point.ixx
)


