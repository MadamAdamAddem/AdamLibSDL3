cmake_minimum_required(VERSION 3.10)


add_library(adam_engine STATIC
  Rendering/rendering.cpp
  Resources/textures.cpp
  Window/window.cpp
)

add_library(adam::engine ALIAS adam_engine)


target_include_directories(adam_engine
    PUBLIC
     ${PROJECT_SOURCE_DIR}/include
)
