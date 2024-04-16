cmake_minimum_required(VERSION 3.29)

project(dsalgcpp
    VERSION 0.0.1
    LANGUAGES CXX
)
add_compile_options(
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Debug>:-Wall>
    $<$<CONFIG:Debug>:-Werror>
)

include(FetchContent)
find_package(Git REQUIRED)

FetchContent_Declare(
    doctest
    SOURCE_DIR ${CMAKE_BINARY_DIR}/doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG origin/master 
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
FetchContent_MakeAvailable(doctest)
set(DOCTEST_INCLUDE_DIR ${CMAKE_BINARY_DIR}/doctest/doctest)

include(${CMAKE_BINARY_DIR}/doctest/scripts/cmake/doctest.cmake)

add_executable(tests 
    tests/linked_list.cc 
    tests/array_list.cc
    tests/stack.cc
    tests/queue.cc
)
target_include_directories(tests PUBLIC ${DOCTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)


enable_testing()
doctest_discover_tests(tests)

