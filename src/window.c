#include <stdlib.h>
#include "window.h"

taida_t *taidaInit(taidaOptions_t options)
{
	if (!glfwInit()) {
		taidaLogError("GLFW Not Initialized");
		
		return NULL;
	}
	taidaLogInfo("GLFW Initialized");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	taida_t *taida = malloc(sizeof(taida_t));
	if (taida == NULL) {
		taidaLogError("Can\'t Create Engine Bases");
		
		taidaClose(taida);
		return NULL;
	}

	taida->window = glfwCreateWindow(options.width, options.height, options.title, NULL, NULL);
	if (taida->window == NULL) {
		taidaLogError("OpenGL Window Cannot Be Created");

		taidaClose(taida);
		return NULL;
	}
	taidaLogInfo("OpenGl Window Created");
	
	glfwMakeContextCurrent(taida->window);
	glfwSetWindowPos(taida->window, options.x, options.y);
	glfwSetErrorCallback(taidaGLFWError);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		taidaLogError("GLAD and OpenGL Not Initialized");

		taidaClose(taida);
		return NULL;
	}
	taidaLogInfo("GLAD and OpenGL Initialized");

	taida->maxFPS = options.FPS;
	taidaLogInfo("Engine Bases Created");

	return taida;
}

void taidaClose(taida_t *taida)
{
	if (taida != NULL) {
		if (taida->window != NULL) {
			glfwDestroyWindow(taida->window);
			taidaLogInfo("Window Destroyed");
		}

		free(taida);
	}

	glfwTerminate();
	taidaLogInfo("Engine Closed and Destroyed");
}
