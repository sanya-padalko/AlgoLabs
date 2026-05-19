#ifndef __INTRO_SORT_H_
#define __INTRO_SORT_H_

#include <stdlib.h>
#include <stdio.h>
#include "small-sortings.h"
#include "part-sortings.h"
#include "hoar-shell.h"
#include "heap-sortings.h"

int max_deep = 1;

int get_log(int n);

void	RecIntro_sort	(uint32_t* arr, int l, int r, 
                            int (*pivot_selector)(uint32_t*, int, int), 
                            int (*partition)(uint32_t*, int, int, int), int deep)	;

void	Intro_sort		(uint32_t* arr, int size)									;

#endif
