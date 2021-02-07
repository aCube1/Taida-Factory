#include <stdlib.h>
#include <stddef.h>
#include "Taida/Core/log.h"
#include "Taida/Graphics/shaders.h"
#include "Taida/Graphics/texture.h"

const char *vertexShaderSource, *fragmentShaderSource;

TaidaTexture_t *taidaCreateNewTexture(const char *filePath)
{
	TaidaTexture_t *texture = malloc(sizeof(TaidaTexture_t));

	if (texture == NULL) {
		taidaLogError("Texture Cannot Be Created");
		return NULL;
	}
	
	float vertices[] = {
		/* Vertices    */	/* Color       */	/* Tex Coords */
		 0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, /* Top Right */
		 0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	1.0f, 0.0f, /* Bottom Right */
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, /* Bottom Left */
		-0.5f,  0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f, /* Top Left */
	};

	int indices[] = {
		0, 1, 3, /* First Triangle (Top Right) */
		1, 2, 3, /* Second Triangle (Bottom Left) */
	};

	vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec2 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"layout (location = 2) in vec2 aTexCoords;\n"
		"out vec3 ourColor;\n"
		"out vec2 TexCoords;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos, 1.0f, 1.0f);\n"
		"	ourColor = aColor;\n"
		"	TexCoords = aTexCoords;\n"
		"}\n";

	fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n"
		"in vec2 TexCoords;\n"
		"uniform sampler2D ourTexture;\n"
		"void main()\n"
		"{\n"
		"	FragColor = texture(ourTexture, TexCoords) * vec4(ourColor, 1.0f);\n"
		"}\n";

	texture->vertexShaderSource = vertexShaderSource;
	texture->fragmentShaderSource = fragmentShaderSource;

	texture->shaderProgram = taidaCreateShaderProgram(texture->vertexShaderSource, texture->fragmentShaderSource);

	if (texture->shaderProgram == 0) {
		taidaLogWarn("Cannot Create ShaderProgram For Texture");
		taidaDestroyTexture(texture);
		return NULL;
	}

	texture->image = taidaLoadNewImage(filePath);

	if (texture->image == NULL) {
		taidaLogError("Texture Cannot Load Image");

		taidaDestroyTexture(texture);
		return NULL;
	}

	glGenVertexArrays(1, &texture->VAO);
	glGenBuffers(1, &texture->VBO);
	glGenBuffers(1, &texture->EBO);
	glGenTextures(1, &texture->texture);
	
	glBindVertexArray(texture->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, texture->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texture->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, texture->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	switch (texture->image->colorType) {
		case TAIDA_IMG_RGB:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->image->width, texture->image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->image->data);
			break;
		case TAIDA_IMG_RGBA:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->image->width, texture->image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->image->data);
			break;
		default:
			taidaLogError("nrChannels Is Unrecognizable");
			taidaDestroyTexture(texture);
			return NULL;
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));

	return texture;
}

void taidaDrawTexture(TaidaTexture_t *texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
	
	glUseProgram(texture->shaderProgram);
	glBindVertexArray(texture->VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void taidaDestroyTexture(TaidaTexture_t *texture)
{
	if (texture) {
		if (texture->image)
			taidaDestroyImage(texture->image);
		
		if (texture->shaderProgram)
			glDeleteProgram(texture->shaderProgram);
		

		free(texture);
	}
}
