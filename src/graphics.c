#include "graphics.h"

GLuint taidaCreateShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource)
{
	int success;
	char infoLog[512];

	GLuint vertexShader, fragmentShader;
	
	GLuint shaderProgram = glCreateProgram();

	vertexShader = taidaCompileVertexShader(vertexShaderSource);
	fragmentShader = taidaCompileFragmentShader(fragmentShaderSource);	

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success || vertexShader == 0 || fragmentShader == 0) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glDeleteProgram(shaderProgram);
		taidaLogWarn(infoLog);
		return 0;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;	
}

GLuint taidaCompileVertexShader(const char *vertexShaderSource)
{
	int success;
	char infoLog[512];

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		
		taidaLogWarn(infoLog);
		return 0;
	}

	return vertexShader;
}

GLuint taidaCompileFragmentShader(const char *fragmentShaderSource)
{
	int success;
	char infoLog[512];

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);

		taidaLogWarn(infoLog);
		return 0;
	}

	return fragmentShader;
}
