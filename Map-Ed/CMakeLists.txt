cmake_minimum_required(VERSION 3.20)
project(Map-Ed CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")


add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui
)

target_link_libraries(${PROJECT_NAME} PRIVATE Core)

add_custom_target(copy_editor_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/../assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)
add_dependencies(${PROJECT_NAME} copy_editor_assets)