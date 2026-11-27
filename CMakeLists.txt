cmake_minimum_required(VERSION 4.3)
project(car_racer CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
)
FetchContent_MakeAvailable(raylib)

add_executable(
        car_racer
        src/main.cpp
        src/car.cpp
        src/camera_controller.cpp
        src/checkpoints.cpp
)
target_link_libraries(car_racer raylib)