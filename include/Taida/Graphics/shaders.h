#ifndef _SHADERS_H_
#define _SHADERS_H_

#include "glad/glad.h"

enum taidaShaderType{
	TAIDA_VERTEXSHADER,
	TAIDA_FRAGMENTSHADER,
};

GLuint taidaCreateShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource);

GLuint taidaCompileShader(const char *shaderSource, int shaderType);

#endif /* _SHADERS_H_ */
