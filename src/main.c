#include <stdlib.h>
#include <stdio.h>
#include "core.h"
#include "window.h"
#include "graphics.h"

int main(int argv, char *argc[])
{
	taida_t *taida = taidaInit((taidaOptions_t) {
			.title = "Factory",

			.width = 800, .height = 600,
			});

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, /* left bottom */
		 0.5f, -0.5f, 0.0f, /* right bottom */
		 0.0f,  0.5f, 0.0f, /* center */
	};

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

	GLuint VBO, VAO, shaderProgram;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	shaderProgram = taidaCreateShaderProgram(vertexShaderSource, fragmentShaderSource);

	while (!glfwWindowShouldClose(taida->window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		
		/* BeginDraw */
		glDrawArrays(GL_TRIANGLES, 0, 3);
		/* EndDraw */

		glDisableVertexAttribArray(0);
		glfwSwapBuffers(taida->window);
		glfwPollEvents();
	};

	taidaClose(taida);

	return 0;
}
