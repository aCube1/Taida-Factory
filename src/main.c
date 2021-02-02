#include <stdlib.h>
#include <stdio.h>
#include "window.h"
#include "graphics.h"
#include "primitives.h"
#include "time.h"

int main(int argv, char *argc[])
{
	taida_t *taida = taidaInit((taidaOptions_t) {
			.title = "Factory",
			
			.FPS = 60.f,
			.width = 800, .height = 600,
			});

	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"}\n";

	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 fragColor;\n"
		"void main()\n"
		"{\n"
		"	fragColor = vec4(0.0f, 0.5f, 1.0f, 1.0f);"
		"}\n";

	taidaShaderSource_t shaderSource = {
		.vertex = vertexShaderSource,
		.fragment = fragmentShaderSource,
	};

	taidaRectangle_t *rectangle = taidaCreateRectangle(&shaderSource);

	glfwSwapInterval(0);
	taida->lastFrameTime = glfwGetTime();
	while (!glfwWindowShouldClose(taida->window)) {
		taida->currentTime = glfwGetTime();
		taida->deltaTime = taida->currentTime - taida->lastFrameTime;
		
		glClear(GL_COLOR_BUFFER_BIT);

		/* BeginDraw */
		taidaDrawRectangle(rectangle);
		/* EndDraw */
			
		glfwSwapBuffers(taida->window);	
		glfwPollEvents();
		if (taida->deltaTime < 1000.f / taida->maxFPS)
			taidaDelay((1000.f / taida->maxFPS) - taida->deltaTime);
		
		taida->lastFrameTime = taida->currentTime;
	};
	glDisableVertexAttribArray(0);

	taidaClose(taida);

	return 0;
}
