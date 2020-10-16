cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
        SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)


# TODO: rename project and delete this comment
project(template)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

# TODO: change template word to project name and delete this comment
add_library(template STATIC
        # enum your files and delete this comment
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/analytics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/experiment.cpp
        )
add_executable(tests
        # TODO: enum your files and delete this comment
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/analytics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/experiment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/lab2.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
        )

# TODO: change template word to project name and delete this comment
target_include_directories(template
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
target_include_directories(tests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
# TODO: change template word to project name and delete this comment
target_link_libraries(tests GTest::main template)

enable_testing()
add_test(NAME unit_tests COMMAND tests)