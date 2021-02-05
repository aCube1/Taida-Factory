#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "core.h"
#include "log.h"

taida_t *taidaInit(taidaOptions_t options);
void taidaClose(taida_t *taida);

void taidaGLFWFramebuffer(GLFWwindow *window, int width, int height);

#endif /* _WINDOW_H_ */
