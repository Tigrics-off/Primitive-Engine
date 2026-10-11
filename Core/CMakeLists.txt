cmake_minimum_required(VERSION 3.20)
project(Core CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw3 opengl32 gdi32)
    if(NOT MSVC)
        target_link_options(${PROJECT_NAME} PRIVATE -static -static-libgcc -static-libstdc++)
    endif()
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw GL X11 pthread dl)
endif()