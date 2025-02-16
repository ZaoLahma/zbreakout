# cpp/core/CMakeLists.txt

add_library(zbreakout_core STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/message_broker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sdl_renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sdl_window.cpp
    # Add other core source files here
)

target_include_directories(zbreakout_core
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_include_directories(zbreakout_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# SDL2 stuff
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_library               (external.sdl2 INTERFACE)
target_include_directories(external.sdl2 INTERFACE ${SDL2_INCLUDE_DIRS})
target_link_libraries     (external.sdl2 INTERFACE ${SDL2_LIBRARIES})

target_link_libraries(zbreakout_core external.sdl2)