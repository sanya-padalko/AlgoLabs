#ifndef __PART_SORTINGS_H_
#define __PART_SORTINGS_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "small-sortings.h"

int (*hoar_pivot)(uint32_t*, int, int) = pivot_central;

int		pivot_central		(uint32_t* arr, int lt, int rt)					;
int		pivot_mediana3		(uint32_t* arr, int lt, int rt)					;
int		pivot_random		(uint32_t* arr, int lt, int rt)					;
int		pivot_random_med	(uint32_t* arr, int lt, int rt)					;

int		hoar_part			(uint32_t* arr, int lt, int rt, int pivot_ind)	;
int		lomuto_part			(uint32_t* arr, int lt, int rt, int pivot_ind)	;
int		thick_part			(uint32_t* arr, int lt, int rt, int pivot_ind)	;

void	Quick_sort			(uint32_t* arr, int lt, int rt, 
                            int (*pivot_selector)(uint32_t*, int, int), 
                            int (*partition)(uint32_t*, int, int, int))		;
void	Hoar_sort			(uint32_t* arr, int size)						;
void	Lomuto_sort			(uint32_t* arr, int size)						;
void	Thick_sort			(uint32_t* arr, int size)						;

#endif