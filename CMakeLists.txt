cmake_minimum_required(VERSION 3.19)
project(PrimitiveEngine)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/glad.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw3
        opengl32
)