#include <stdlib.h>
#include <stdio.h>
#include "core.h"
#include "window.h"

int main(int argv, char *argc[])
{
	taida_t *taida = taidaInit((taidaOptions_t) {
			.title = "Factory",

			.width = 800, .height = 600,
			});

	while (!glfwWindowShouldClose(taida->window)) {


		glfwSwapBuffers(taida->window);
		glfwPollEvents();
	};

	taidaClose(taida);

	return 0;
}
