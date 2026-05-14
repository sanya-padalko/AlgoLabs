#ifndef _ASSERTS_H_
#define _ASSERTS_H_

#include <assert.h>
#include <stdio.h>

#ifdef DEBUG
	#define MY_ASSERT(condition, ...)									\
		do {														\
			if (!(condition)) {										\
				fprintf(stderr, "ASSERTION FAILED in %s (%s:%d)\n",	\
						__func__, __FILE__, __LINE);				\
				fprintf(stderr, __VA_ARGS__);						\
				assert(0);											\
			}														\
		} while (0)
#else
	#define MY_ASSERT(condition, ...)
#endif

#endif