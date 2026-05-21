#include <stdio.h>
#include <stdlib.h>

int K_HEAP = 2;

int		get_parent			(int ind)							;
int		get_child			(int node_ind, int ch_ind)			;

void	sift_down			(uint32_t *arr, int size, int ind)	;

void	Bottom_up_heap_sort	(uint32_t *arr, int size)			;