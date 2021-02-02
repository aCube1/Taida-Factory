#include "primitives.h"

taidaRectangle_t *taidaCreateRectangle(taidaShaderSource_t *shaderSource)
{
	taidaRectangle_t *rectangle = malloc(sizeof(taidaRectangle_t));
	
	if (rectangle == NULL) {
		taidaLogWarn("Cannot Create Rectangle");
		return NULL;
	}

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, /* left bottom */
		 0.5f, -0.5f, 0.0f, /* right bottom */
		 0.5f,  0.5f, 0.0f, /* left top */
		-0.5f,  0.5f, 0.0f, /* right top */
	};

	int indices[] = {
		0, 1, 2, /* left bottom */
		0, 2, 3, /* right bottom */
	};

	rectangle->shaderProgram = taidaCreateShaderProgram(shaderSource->vertex, shaderSource->fragment);

	if (rectangle->shaderProgram == 0) {
		taidaLogWarn("Cannot Create ShaderProgram For Rectangle");
		free(rectangle);
		return NULL;
	}

	glGenVertexArrays(1, &rectangle->VAO);
	glBindVertexArray(rectangle->VAO);

	glGenBuffers(1, &rectangle->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, rectangle->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &rectangle->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	return rectangle;
}

void taidaDrawRectangle(taidaRectangle_t *rectangle)
{
	glBindBuffer(GL_ARRAY_BUFFER, rectangle->VBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
	
	glUseProgram(rectangle->shaderProgram);
	glBindVertexArray(rectangle->VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
