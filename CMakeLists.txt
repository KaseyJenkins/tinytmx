cmake_minimum_required(VERSION 3.20)
project(tinytmxGit)

option(BUILD_TESTING "Build tests" OFF)

if(BUILD_TESTING)
	enable_testing()
endif()

include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

add_library(project_warnings INTERFACE)
# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# Build the targets
add_subdirectory(lib)
# Tests
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()