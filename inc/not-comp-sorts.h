#ifndef __NOT_COMP_H_
#define __NOT_COMP_H_

#include <string.h>
#include <stdlib.h>

#define MAX 256

void	LSD_sort	(unsigned int* arr, int size)									;

void	RecMSD_sort	(unsigned int* arr, int l, int r, unsigned int mask, int shift)	;

void	MSD_sort	(unsigned int* arr, int size)									;

#endif