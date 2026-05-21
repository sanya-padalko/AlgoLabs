#ifndef _MERGE_SORTS_
#define _MERGE_SORTS_

#include <stdlib.h>
#include <stdio.h>

extern uint32_t* add_arr;

void	MergeSeg		(uint32_t* arr, int lt, int mid, int rt);

void	RecMergeSort	(uint32_t* arr, int lt, int rt)			;

void	GoRecMerge_sort	(uint32_t* arr, int size)				;

void	IterMerge_sort	(uint32_t* arr, int size)				;

#endif