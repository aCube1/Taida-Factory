#ifndef _CORE_H_
#define _CORE_H_

#include <stdbool.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "cglm/cglm.h"

typedef struct {
	GLFWwindow *window;

	struct {
		GLuint shaderProgram;

		GLuint VBO, VAO, EBO;

		const char *vertexShaderSource, *fragmentShaderSource;	
	} shape;

	bool shapeInitialized;
	float maxFPS, deltaTime;
	double lastUpdateTime, lastFrameTime, currentTime;
} taida_t;

typedef struct {
	char *title;

	float FPS;

	int x, y;
	int width, height;
} taidaOptions_t;

#endif /* _CORE_H_ */

