#include <stdlib.h>
#include <stdio.h>
#include "Taida/taidaCore.h"
#include "Taida/taidaGraphics.h"

int main(int argv, char *argc[])
{
	Taida_t *taida = taidaInit((TaidaOptions_t) {
			.title = "Factory",
			
			.FPS = 60.f,
			.width = 800, .height = 600,
			});

	/* taidaInitShapes(taida); */

	TaidaTexture_t *texture = taidaCreateNewTexture("../res/cube");

	glfwSwapInterval(0);
	taida->lastFrameTime = glfwGetTime();
	while (!glfwWindowShouldClose(taida->window)) {
		taida->currentTime = glfwGetTime();
		taida->deltaTime = taida->currentTime - taida->lastFrameTime;
	
		glClearColor(0.0f, 0.5f, 1.0f, 1.0f);	
		glClear(GL_COLOR_BUFFER_BIT);
		/* BeginDraw */
		
		/* taidaDrawRectangle(taida); */
		if (texture != NULL)
			taidaDrawTexture(texture);

		/* EndDraw */
			
		glfwSwapBuffers(taida->window);	
		glfwPollEvents();
		if (taida->deltaTime < 1000.f / taida->maxFPS)
			taidaDelay((1000.f / taida->maxFPS) - taida->deltaTime);
		
		taida->lastFrameTime = taida->currentTime;
	};
	taidaDestroyTexture(texture);

	taidaClose(taida);

	return 0;
}
