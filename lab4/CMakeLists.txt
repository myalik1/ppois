cmake_minimum_required(VERSION 3.14)
project(Lab4_Graph_Sorting CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(lab4_lib
    src/cli/console_menu.cpp
)

add_executable(lab4_app
    src/main.cpp
)
target_link_libraries(lab4_app PRIVATE lab4_lib)

add_executable(lab4_tests
    tests/test_selection_sort.cpp
    tests/test_bucket_sort.cpp
    tests/test_vertex.cpp
    tests/test_edge.cpp
    tests/test_undirected_graph.cpp
    tests/test_vertex_iterator.cpp
    tests/test_edge_iterator.cpp
    tests/test_incident_iterator.cpp
    tests/test_adjacent_iterator.cpp
)
target_link_libraries(lab4_tests PRIVATE lab4_lib gtest_main)

include(GoogleTest)
gtest_discover_tests(lab4_tests)
