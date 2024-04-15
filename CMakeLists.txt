cmake_minimum_required(VERSION 3.29)

project(dsalgcpp
    VERSION 0.0.1
    LANGUAGES CXX
)
add_compile_options(
    -g
    -Wall
    -Werror
)

include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    doctest
    PREFIX ${CMAKE_BINARY_DIR}/doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

# Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")
include(${source_dir}/scripts/cmake/doctest.cmake)

enable_testing()

add_executable(linked_list src/linked_list.cc)
target_include_directories(linked_list PUBLIC ${DOCTEST_INCLUDE_DIR})
doctest_discover_tests(linked_list)

