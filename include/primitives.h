#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#include "core.h"
#include "graphics.h"

void taidaInitPrimitives(taida_t *taida);
void taidaDrawRectangle(taida_t *taida);

taidaTexture_t *taidaCreateTexture(const char *filename);
void taidaDrawTexture(taidaTexture_t *texture); 

void taidaDestroyTexture(taidaTexture_t *texture);

#endif /* _PRIMITIVES_H_ */
