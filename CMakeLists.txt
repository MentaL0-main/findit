cmake_minimum_required(VERSION 3.10)

project(findit CXX)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(GLEW REQUIRED)

add_executable(findit src/main.cpp
                      src/core/application.cpp
                      src/graphics/window.cpp
                      src/graphics/renderer.cpp
                      src/graphics/object.cpp
                      src/graphics/shader.cpp
                      src/input/keyboard.cpp
                      src/input/mouse.cpp
                      src/ResourceManager/ResourceManager.cpp
                      src/camera/camera.cpp
                      src/controller/controller.cpp
                      src/logger/logger.cpp)

target_link_libraries(findit PRIVATE SDL3::SDL3)
target_link_libraries(findit PRIVATE GLEW::GLEW)
target_link_libraries(findit PRIVATE SDL3_image::SDL3_image)
target_link_libraries(findit PRIVATE GL)

target_compile_options(findit PRIVATE "-g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
