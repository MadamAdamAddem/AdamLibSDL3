cmake_minimum_required(VERSION 3.10)
project(adam_lib)

add_library(adam_lib STATIC
  Window/window.cpp
  Renderer/renderer.cpp
  Resources/manager.cpp
  Resources/Textures/textures.cpp
  Input/inputs.cpp
)

add_library(adam::lib ALIAS adam_lib)

target_include_directories(adam_lib
    PUBLIC
     ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(adam_lib
  PUBLIC
    SDL3::SDL3
    $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,
       SDL3_image::SDL3_image-shared, SDL3_image::SDL3_image-static>
    $<IF:$<TARGET_EXISTS:SDL3_ttf::SDL3_ttf-shared>,
       SDL3_ttf::SDL3_ttf-shared, SDL3_ttf::SDL3_ttf-static>
)
