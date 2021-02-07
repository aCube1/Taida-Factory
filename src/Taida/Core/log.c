#include <stdio.h>
#include "Taida/Core/log.h"

void taidaLog(const int priority, const char *msg)
{
	switch (priority) {
		case TAIDA_LOGP_ERROR:
			fprintf(stderr, "[ERROR] TAIDA - %s\n", msg);
			break;
		case TAIDA_LOGP_WARN:
			fprintf(stdout, "[WARN] TAIDA - %s\n", msg);
			break;
		case TAIDA_LOGP_DEBUG:
			fprintf(stdout, "[DEBUG] TAIDA - %s\n", msg);
			break;
		case TAIDA_LOGP_INFO:
			fprintf(stdout, "[INFO] TAIDA - %s\n", msg);
			break;
		case TAIDA_LOGP_GLFW_ERROR:
			fprintf(stderr, "[GLFW ERROR] TAIDA - %s\n", msg);
	}
}

void taidaGLFWError(int code, const char *msg) 
{
	taidaLog(TAIDA_LOGP_GLFW_ERROR, msg);
}

