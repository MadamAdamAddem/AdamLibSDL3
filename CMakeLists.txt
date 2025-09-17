cmake_minimum_required(VERSION 3.10)


project(adam_engine)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED CONFIG REQUIRED COMPONENTS SDL3_image-shared)
find_package(SDL3_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL3_ttf-shared)


add_subdirectory(src)




add_executable(binary main.cpp)


target_link_libraries(binary
    PRIVATE
        ${SDL3}
        ${SDL3_image}
        ${SDL3_ttf}
        adam::engine

)