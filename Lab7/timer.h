#include <time.h>

static double GetTime() {
	return (double)clock() * 1000.0 / CLOCKS_PER_SEC;
}