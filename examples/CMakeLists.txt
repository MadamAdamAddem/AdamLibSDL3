add_executable(binary main.cpp testgame.cpp)

target_include_directories(binary
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(binary
  PRIVATE
    adam::lib
)
