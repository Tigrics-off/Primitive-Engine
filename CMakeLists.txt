cmake_minimum_required(VERSION 3.19)
project(PrimitiveEngine)

file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/glad.c
)

add_library(imgui
    include/imgui/imgui.cpp
    include/imgui/imgui_draw.cpp
    include/imgui/imgui_tables.cpp
    include/imgui/imgui_widgets.cpp
    include/imgui/backends/imgui_impl_glfw.cpp
    include/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    include
    include/imgui
    include/imgui/backends
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        imgui
        glfw3
        opengl32
)