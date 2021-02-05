#include <stddef.h>
#include "Taida/Core/log.h"
#include "Taida/Graphics/shaders.h"

GLuint taidaCreateShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource)
{
	int success;
	char infoLog[512];

	GLuint vertexShader, fragmentShader;
	GLuint shaderProgram = glCreateProgram();

	vertexShader = taidaCompileShader(vertexShaderSource, TAIDA_VERTEXSHADER);
	fragmentShader = taidaCompileShader(fragmentShaderSource, TAIDA_FRAGMENTSHADER);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success || vertexShader == 0 || fragmentShader == 0) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glDeleteProgram(shaderProgram);
		
		taidaLogWarn("Program Cannot Be Created");
		taidaLogError(infoLog);
		return 0;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

GLuint taidaCompileShader(const char *shaderSource, int shaderType)
{
	int success;
	char infoLog[512];

	GLuint shader;

	switch (shaderType) {
		case TAIDA_VERTEXSHADER:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case TAIDA_FRAGMENTSHADER:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		default:
			taidaLogWarn("Shader Type Nonexistent");
			return 0;
	}

	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);

		taidaLogWarn("Shader Cannot Be Compiled");
		taidaLogError(infoLog);
	       	return 0;
	}

	return shader;
}
