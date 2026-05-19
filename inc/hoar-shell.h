#ifndef __HOAR_SHELL_H_
#define __HOAR_SHELL_H_

#include <stdlib.h>
#include <stdio.h>
#include "small-sortings.h"
#include "part-sortings.h"

int block_size = 1;

void Hoar_Shell_sort(uint32_t* arr, int l, int r, 
                        int (*pivot_selector)(uint32_t*, int, int), 
                        int (*partition)(uint32_t*, int, int, int))	;

void HoarShell_sort(uint32_t* arr, int size)						;

#endif
