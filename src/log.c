#include <stdio.h>
#include "log.h"

void taidaLog(const int priority, const char *msg)
{
	switch (priority) {
		case TLOGP_ERROR:
			fprintf(stderr, "[ERROR] TAIDA - %s\n", msg);
			break;
		case TLOGP_WARN:
			fprintf(stdout, "[WARN] TAIDA - %s\n", msg);
			break;
		case TLOGP_DEBUG:
			fprintf(stdout, "[DEBUG] TAIDA - %s\n", msg);
			break;
		case TLOGP_INFO:
			fprintf(stdout, "[INFO] TAIDA - %s\n", msg);
			break;
		case TLOGP_GLFW_ERROR:
			fprintf(stderr, "[GLFW ERROR] TAIDA - %s\n", msg);
	}
}

void taidaGLFWError(int code, const char *msg) 
{
	taidaLog(TLOGP_GLFW_ERROR, msg);
}

