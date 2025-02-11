# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(zBreakout)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source directories
add_subdirectory(cpp/core)
add_subdirectory(cpp/game)

add_executable(${PROJECT_NAME} cpp/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE zbreakout_game zbreakout_core)