#ifndef __BINARY_HEAP__
#define __BINARY_HEAP__

#include <stdlib.h>
#include <string.h>

void	swap		(void* arg1, void* arg2, size_t size)	;

void	sift_down	(int *arr, int n, int ind)		;
void	sift_up		(int *arr, int ind)				;

void	build_heap	(int *arr, int n)				;

#endif