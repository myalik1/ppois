cmake_minimum_required(VERSION 3.16)
project(AirportSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_COVERAGE "Enable coverage reporting" ON)

if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE DOMAIN_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/passengers/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ticketing/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/aircraft/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/crew/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/operations/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/security/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/services/*.cpp"
)

add_library(airport_core STATIC ${DOMAIN_SOURCES})

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    add_executable(airport_app
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cli/AirportCLI.cpp
    )
    target_link_libraries(airport_app PRIVATE airport_core)
endif()

enable_testing()
find_package(GTest REQUIRED)

file(GLOB_RECURSE TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
)

add_executable(run_tests ${TEST_SOURCES})
target_link_libraries(run_tests PRIVATE airport_core GTest::gtest GTest::gtest_main pthread)
add_test(NAME AirportUnitTests COMMAND run_tests)
