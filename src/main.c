#include <stdlib.h>
#include <stdio.h>
#include "window.h"
#include "primitives.h"
#include "time.h"

int main(int argv, char *argc[])
{
	taida_t *taida = taidaInit((taidaOptions_t) {
			.title = "Factory",
			
			.FPS = 60.f,
			.width = 800, .height = 600,
			});

	taidaTexture_t *texture = taidaCreateTexture("../res/wall.jpg");

	glfwSwapInterval(0);
	taida->lastFrameTime = glfwGetTime();
	while (!glfwWindowShouldClose(taida->window)) {
		taida->currentTime = glfwGetTime();
		taida->deltaTime = taida->currentTime - taida->lastFrameTime;
	
		glClearColor(0.0f, 0.5f, 1.0f, 1.0f);	
		glClear(GL_COLOR_BUFFER_BIT);
		/* BeginDraw */
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
