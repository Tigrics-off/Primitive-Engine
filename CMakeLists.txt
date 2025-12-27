cmake_minimum_required(VERSION 3.19)
project(PrimitiveEngine)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

add_library(imgui
    include/imgui/imgui.cpp
    include/imgui/imgui_draw.cpp
    include/imgui/imgui_tables.cpp
    include/imgui/imgui_widgets.cpp

    include/imgui/backends/imgui_impl_glfw.cpp
    include/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC include/imgui include/imgui/backend)

target_link_libraries(${PROJECT_NAME} imgui glfw glad)