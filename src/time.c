#include "time.h"

void taidaDelay(unsigned int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms * 1000);
#endif /* _WIN32 */
}
