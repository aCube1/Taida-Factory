#ifndef _CORE_H_
#define _CORE_H_

#include <stdbool.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

typedef struct taida {
	GLFWwindow *window;

	int maxFPS;
	float deltaTime;
} taida_t;

typedef struct taidaOptions {
	char *title;

	int FPS;

	int x, y;
	int width, height;
} taidaOptions_t;

#endif /* _CORE_H_ */

