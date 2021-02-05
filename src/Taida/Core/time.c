#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif /* _WIN32 */

#include "Taida/Core/time.h"

void taidaDelay(unsigned int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms * 1000);
#endif /* _WIN32 */
}
