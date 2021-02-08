cmake_minimum_required(VERSION 3.1.8)

project(Taida)

set(CMAKE_C_FLAGS "-pedantic")
set(CMAKE_C_STANDARD 99)

set(PROJECT_VERSION 0.0.10)

option(TAIDA_BUILD_SHAREDLIBS "Build Shared Libs" OFF)

option(CGLM_SHARED "" OFF)
option(CGLM_STATIC "" ON)
option(CGLM_USE_C99 "" ON)
option(CGLM_USE_TESTS "" OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(ext/cglm)
add_subdirectory(ext/glfw)
add_subdirectory(ext/glad)

add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PUBLIC "include" "ext/stb/include")
