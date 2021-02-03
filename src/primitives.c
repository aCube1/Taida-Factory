#include "primitives.h"

void taidaInitPrimitives(taida_t *taida)
{
	float vertices[] = {
		/* Position */      /* Color */
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, /* left bottom */
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, /* right bottom */
		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, /* left top */
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, /* right top */
	};

	int indices[] = {
		0, 1, 2, /* left top */
		0, 2, 3, /* right bottom */
	};

	const char defaultVertexShader[] = "#version 330 core\n"
		"layout (location = 0) in vec2 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, 1.0f, 1.0f);\n"
		"	ourColor = aColor;\n"
		"}\n";

	const char defaultFragmentShader[] = "#version 330 core\n"
		"in vec3 ourColor;\n"
		"out vec4 fragColor;\n"
		"void main()\n"
		"{\n"
		"	fragColor = vec4(ourColor, 1.0f);\n"
		"}\n";
	
	taida->rectangle.vertexShaderSource = defaultVertexShader;
	taida->rectangle.fragmentShaderSource = defaultFragmentShader;

	taida->rectangle.shaderProgram = taidaCreateShaderProgram(taida->rectangle.vertexShaderSource, taida->rectangle.fragmentShaderSource);

	if (taida->rectangle.shaderProgram == 0) {
		taidaLogWarn("Cannot Create ShaderProgram For Rectangle");
		return;
	}

	glGenBuffers(1, &taida->rectangle.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, taida->rectangle.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &taida->rectangle.VAO);
	glBindVertexArray(taida->rectangle.VAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);

	glEnableVertexAttribArray(1);	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
	
	glGenBuffers(1, &taida->rectangle.EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, taida->rectangle.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	taida->primitivesInitialized = true;
}

void taidaDrawRectangle(taida_t *taida)
{	
	glUseProgram(taida->rectangle.shaderProgram);
	glBindVertexArray(taida->rectangle.VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

