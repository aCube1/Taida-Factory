#include <stdlib.h>
#include <stdio.h>
#include "window.h"
#include "graphics.h"
#include "primitives.h"
#include "time.h"

int main(int argv, char *argc[])
{
	taida_t *taida = taidaInit((taidaOptions_t) {
			.title = "Factory",
			
			.FPS = 60.f,
			.width = 800, .height = 600,
			});

	taidaInitPrimitives(taida);

	glfwSwapInterval(0);
	taida->lastFrameTime = glfwGetTime();
	while (!glfwWindowShouldClose(taida->window)) {
		taida->currentTime = glfwGetTime();
		taida->deltaTime = taida->currentTime - taida->lastFrameTime;
		
		glClear(GL_COLOR_BUFFER_BIT);
		/* BeginDraw */
		taidaDrawRectangle(taida);
		/* EndDraw */
			
		glfwSwapBuffers(taida->window);	
		glfwPollEvents();
		if (taida->deltaTime < 1000.f / taida->maxFPS)
			taidaDelay((1000.f / taida->maxFPS) - taida->deltaTime);
		
		taida->lastFrameTime = taida->currentTime;
	};

	taidaClose(taida);

	return 0;
}
