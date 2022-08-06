cmake_minimum_required(VERSION 3.7)
project(logger)

set(CMAKE_CXX_STANDARD 17)

file(GLOB sources "src/*")
add_library(logger ${sources})

target_include_directories(logger PUBLIC "include/")

get_property(TARGETS DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
get_directory_property(HAS_PARENT PARENT_DIRECTORY)

if(HAS_PARENT)
    set(LOGGER_INCLUDES "${PROJECT_SOURCE_DIR}/include" PARENT_SCOPE)
    set(LOGGER_LIBS "${TARGETS}" PARENT_SCOPE)
endif()
