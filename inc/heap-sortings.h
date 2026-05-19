#include <stdio.h>
#include <stdlib.h>

int K_HEAP = 2;

int		get_parent			(int i)								;
int		get_child			(int i, int j)						;

void	sift_down			(uint32_t *arr, int size, int i)	;

void	Bottom_up_heap_sort	(uint32_t *arr, int size)			;