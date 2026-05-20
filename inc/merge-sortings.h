#include <stdlib.h>
#include <stdio.h>

uint32_t* add_arr = NULL;

void		MergeSeg		(uint32_t* arr, int lt, int mid, int rt);

static void	RecMergeSort	(uint32_t* arr, int lt, int rt)			;

void		GoRecMerge_sort	(uint32_t* arr, int size)				;

static void	IterMerge_sort	(uint32_t* arr, int size)				;
