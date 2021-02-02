#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#include "core.h"
#include "graphics.h"
#include "log.h"

typedef struct {
	GLuint shaderProgram;

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
} taidaRectangle_t;

taidaRectangle_t *taidaCreateRectangle(taidaShaderSource_t *shaderSource);
void taidaDrawRectangle(taidaRectangle_t *rectangle);

#endif /* _PRIMITIVES_H_ */
