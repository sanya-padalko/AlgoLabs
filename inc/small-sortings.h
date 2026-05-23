#ifndef __SORTINGS_H_
#define __SORTINGS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	swap				(void* arg1, void* arg2, int size)	;

void	Insert_sort			(uint32_t* arr, int size)			;
void	Bubble_sort			(uint32_t* arr, int size)			;
void	Select_sort			(uint32_t* arr, int size)			;
void	Shell_sort			(uint32_t* arr, int size)			;
void	OrigShell_sort		(uint32_t* arr, int size)			;

int		check				(int gap)							;

void	PrattShell_sort		(uint32_t* arr, int size)			;
void	CiuraShell_sort		(uint32_t* arr, int size)			;
void	GonnetShell_sort	(uint32_t* arr, int size)			;

#endif