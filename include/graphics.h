#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <stddef.h>
#include "glad/glad.h"
#include "log.h"

GLuint taidaCreateShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource);

GLuint taidaCompileVertexShader(const char *vertexShaderSource);
GLuint taidaCompileFragmentShader(const char *fragmentShaderSource);

#endif /* _GRAPHICS_H_ */
