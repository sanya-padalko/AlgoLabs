#ifndef __BINARY_HEAP__
#define __BINARY_HEAP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	swap		(void* a, void* b, size_t size)	;

void	sift_down	(int *arr, int n, int i)		;
void	sift_up		(int *arr, int i)				;

void	build_heap	(int *arr, int n)				;

#endif