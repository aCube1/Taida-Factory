#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "core.h"
#include "log.h"

Taida_t *taidaInit(TaidaOptions_t options);
void taidaClose(Taida_t *taida);

void taidaGLFWFramebuffer(GLFWwindow *window, int width, int height);

#endif /* _WINDOW_H_ */
