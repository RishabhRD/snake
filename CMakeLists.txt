cmake_minimum_required(VERSION 3.15)
project(snake CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/Sanitizers.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/StaticAnalyzers.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(project_options INTERFACE)
add_library(project_warnings INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

set_project_warnings(project_warnings)
enable_sanitizers(project_options)

option(ENABLE_TESTS "Enable building tests" OFF)
if(ENABLE_TESTS)
    add_subdirectory(tests)
endif()
add_subdirectory(src)
