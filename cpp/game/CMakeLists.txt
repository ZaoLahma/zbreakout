# cpp/game/CMakeLists.txt

add_library(zbreakout_game STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/breakout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/breakout_paddle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/breakout_ball.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/breakout_block.cpp
    # Add other game source files here
)

target_include_directories(zbreakout_game
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(zbreakout_game
    PUBLIC
        zbreakout_core
)