cmake_minimum_required(VERSION 3.1.8)

project(factory)

set(CMAKE_C_FLAGS "-pedantic")
set(CMAKE_C_STANDARD 99)

set(PROJECT_VERSION 0.0.1)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

file(GLOB SRCS "src/*.c")

add_subdirectory(ext/glfw)
add_subdirectory(ext/glad)

add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_link_libraries(${PROJECT_NAME} glad glfw GL X11 pthread Xrandr Xi dl)
