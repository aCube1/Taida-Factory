#include "Taida/Core/log.h"
#include "Taida/Graphics/shaders.h"
#include "Taida/Graphics/shapes.h"

static const char *vertexShaderSource = "", *fragmentShaderSource = "";

void taidaInitShapes(Taida_t *taida)
{
	float vertices[] = {
		/*   Position    */	/* Colors      */
		 0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f, /* Top Right */
		 0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, /* Bottom Right */
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, /* Bottom Left*/
		-0.5f,  0.5f, 0.0f,	1.0f, 1.0f, 0.0f, /* Top Left*/
	};

	unsigned int indices[] = {
		0, 1, 3, /* First Triangle (Top Right) */
		1, 2, 3, /* Second Triangle (Bottom Left) */
	};

	vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec2 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos, 1.0f, 1.0f);\n"
		"	ourColor = aColor;\n"
		"}\0";

	fragmentShaderSource = "#version 330 core\n"
		"in vec3 ourColor;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(ourColor, 1.0f);\n"
		"}\0";

	taida->Shape.vertexShaderSource = vertexShaderSource;
	taida->Shape.fragmentShaderSource = fragmentShaderSource;

	taida->Shape.shaderProgram = taidaCreateShaderProgram(taida->Shape.vertexShaderSource, taida->Shape.fragmentShaderSource);

	if (taida->Shape.shaderProgram == 0) {
		taidaLogWarn("Cannot Create ShaderProgram For Shape");
		return;
	}

	glGenVertexArrays(1, &taida->Shape.VAO);
	glGenBuffers(1, &taida->Shape.VBO);	
	glGenBuffers(1, &taida->Shape.EBO);
	
	glBindVertexArray(taida->Shape.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, taida->Shape.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, taida->Shape.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));

	taidaLogInfo("Shapes Initiliazed");
	taida->shapeInitialized = true;
}

void taidaDrawRectangle(Taida_t *taida)
{
	glUseProgram(taida->Shape.shaderProgram);
	glBindVertexArray(taida->Shape.VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
