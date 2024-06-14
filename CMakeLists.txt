cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

set(RAYLIB_VERSION 4.5.0)
FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

add_executable(untitled
        src/main.cpp
        src/alien.cpp
        src/block.cpp
        src/laser.cpp
        src/mysteryship.cpp
        src/obstacle.cpp
        src/spaceship.cpp
        src/game.cpp
        src/alien.hpp
        src/block.hpp
        src/laser.hpp
        src/mysteryship.hpp
        src/obstacle.hpp
        src/spaceship.hpp
        src/game.hpp
)
target_link_libraries(${PROJECT_NAME} raylib)

include_directories(doctest)

add_executable(my_test test.cpp src/spaceship.cpp src/mysteryship.cpp src/laser.cpp src/obstacle.cpp src/block.cpp src/alien.cpp src/game.cpp)
target_link_libraries(my_test raylib)

target_include_directories(my_test PRIVATE doctest)

enable_testing()

add_test(NAME my_test COMMAND my_test)
