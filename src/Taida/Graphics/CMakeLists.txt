set(MODULE_NAME taidaGraphics)

file(GLOB SRCS "*.c")

if (TAIDA_BUILD_SHAREDLIBS)
	add_library(${MODULE_NAME} SHARED ${SRCS})
else ()
	add_library(${MODULE_NAME} STATIC ${SRCS})
endif ()

target_link_libraries(${MODULE_NAME} taidaCore cglm glad glfw GL X11 pthread Xrandr Xi dl)
target_include_directories(${MODULE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/ext/stb/include)
