set(MODULE_NAME taidaGraphics)

file(GLOB SRCS "shapes.c" "shaders.c")

add_library(${MODULE_NAME} STATIC ${SRCS})

target_link_libraries(${MODULE_NAME} cglm glad glfw GL X11 pthread Xrandr Xi dl)
target_include_directories(${MODULE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/ext/stb/include)
