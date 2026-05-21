#ifndef _HEAP_SORTS_H_
#define _HEAP_SORTS_H_

#include <stdio.h>
#include <stdlib.h>

extern int K_HEAP;

int		get_parent			(int ind)							;
int		get_child			(int node_ind, int ch_ind)			;

void	sift_down			(uint32_t *arr, int size, int ind)	;

void	Bottom_up_heap_sort	(uint32_t *arr, int size)			;

#endif