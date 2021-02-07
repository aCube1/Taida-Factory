#include <stdlib.h>
#include "Taida/Core/window.h"

Taida_t *taidaInit(TaidaOptions_t options)
{
	if (!glfwInit()) {
		taidaLogError("GLFW Not Initialized");
		
		return NULL;
	}
	taidaLogInfo("GLFW Initialized");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Taida_t *taida = malloc(sizeof(Taida_t));
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
	glfwSetWindowSizeLimits(taida->window, options.width, options.height, GLFW_DONT_CARE, GLFW_DONT_CARE);
	glfwSetErrorCallback(taidaGLFWError);
	glfwSetFramebufferSizeCallback(taida->window, taidaGLFWFramebuffer);

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

void taidaClose(Taida_t *taida)
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

void taidaGLFWFramebuffer(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
