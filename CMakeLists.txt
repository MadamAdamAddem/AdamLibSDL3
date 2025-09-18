cmake_minimum_required(VERSION 3.10)
project(adam_engine)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

add_subdirectory(src)

add_executable(binary main.cpp)

target_link_libraries(binary
  PRIVATE
    adam::lib
    SDL3::SDL3

    $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,
       SDL3_image::SDL3_image-shared, SDL3_image::SDL3_image-static>
    $<IF:$<TARGET_EXISTS:SDL3_ttf::SDL3_ttf-shared>,
       SDL3_ttf::SDL3_ttf-shared, SDL3_ttf::SDL3_ttf-static>
)
