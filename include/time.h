#ifndef _TIME_H_
#define _TIME_H_

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif /* _WIN32 */

void taidaDelay(unsigned int ms);

#endif /* _TIME_H_ */
