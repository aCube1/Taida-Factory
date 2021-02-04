#define STB_IMAGE_IMPLEMENTATION 

#include "stb_image.h"
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
		"}\0";

	const char defaultFragmentShader[] = "#version 330 core\n"
		"in vec3 ourColor;\n"
		"out vec4 fragColor;\n"
		"void main()\n"
		"{\n"
		"	fragColor = vec4(ourColor, 1.0f);\n"
		"}\0";
	
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

taidaTexture_t *taidaCreateTexture(const char *filepath)
{
	taidaTexture_t *texture = malloc(sizeof(taidaTexture_t));

	if (texture == NULL) {
		taidaLogError("Cannot Create Texture");
		return NULL;
	}
	
	float vertices[] = {
		/* Position */      /* Color */       /* Texture Coords */
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, /* left bottom */
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, /* right bottom */
		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, /* left top */
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, /* right top */
	};

	int indices[] = {
		0, 1, 2, /* left top */
		0, 2, 3, /* right bottom */
	};

	const char defaultVertexShader[] = "#version 330 core\n"
		"layout (location = 0) in vec2 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"layout (location = 2) in vec2 aTexCoord;\n"
		"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos, 1.0f, 1.0f);\n"
		"	ourColor = aColor;\n"
		"	TexCoord = aTexCoord;\n"
		"}\0";

	const char defaultFragmentShader[] = "#version 330 core\n"
		"in vec3 ourColor;\n"
		"in vec2 TexCoord;\n"
		"out vec4 fragColor;\n"
		"uniform sampler2D ourTexture;\n"
		"void main()\n"
		"{\n"
		"	fragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f);\n"
		"}\0";
	
	texture->vertexShaderSource = defaultVertexShader;
	texture->fragmentShaderSource = defaultFragmentShader;

	texture->shaderProgram = taidaCreateShaderProgram(texture->vertexShaderSource, texture->fragmentShaderSource);

	if (texture->shaderProgram == 0) {
		taidaLogWarn("Cannot Create ShaderProgram For Mesh");
		taidaDestroyTexture(texture);
		return NULL;
	}

	glGenBuffers(1, &texture->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, texture->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glGenVertexArrays(1, &texture->VAO);
	glBindVertexArray(texture->VAO);

	glGenBuffers(1, &texture->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texture->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);

	glEnableVertexAttribArray(1);	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
	
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filepath, &width, &height, &nrChannels, 0);	
	
	if (data) {
		glUseProgram(texture->shaderProgram);	
		glGenTextures(1, &texture->texture);
		glBindTexture(GL_TEXTURE_2D, texture->texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
		glUniform1i(glGetUniformLocation(texture->shaderProgram, "ourTexture"), 0);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		taidaLogError("Cannot Create Texture");
	}
	stbi_image_free(data);

	taidaLogInfo("Texture Created");
	return texture;
}

void taidaDrawTexture(taidaTexture_t *texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
	glUseProgram(texture->shaderProgram);
	glBindVertexArray(texture->VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void taidaDestroyTexture(taidaTexture_t *texture)
{
	if (texture) {
		if (texture->shaderProgram)
			glDeleteProgram(texture->shaderProgram);

		if (texture->texture)
			glDeleteTextures(1, &texture->texture);
			
		taidaLogInfo("Texture Destroyed");	
		free(texture);
	}
}
