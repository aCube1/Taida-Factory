#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "glad/glad.h"
#include "Taida/Graphics/images.h"

typedef struct {
	GLuint shaderProgram;
	
	GLuint VAO, VBO, EBO;
	GLuint texture;

	TaidaImage_t *image;

	const char *vertexShaderSource, *fragmentShaderSource;
} TaidaTexture_t;

TaidaTexture_t *taidaCreateNewTexture(const char *filePath);
void taidaDrawTexture(TaidaTexture_t *texture);
void taidaDestroyTexture(TaidaTexture_t *texture);

#endif /* _TEXTURE_H_ */
