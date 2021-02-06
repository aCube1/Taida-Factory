#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "glad/glad.h"
#include "Taida/Graphics/images.h"

typedef struct {
	GLuint shaderProgram;
	
	GLuint VAO, VBO, EBO;
	GLuint texture;

	taidaImage_t *image;

	const char *vertexShaderSource, *fragmentShaderSource;
} taidaTexture_t;

taidaTexture_t *taidaCreateNewTexture(const char *filePath);
void taidaDrawTexture(taidaTexture_t *texture);
void taidaDestroyTexture(taidaTexture_t *texture);

#endif /* _TEXTURE_H_ */
