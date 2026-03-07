#ifndef __VECTOR_H_
#define __VECTOR_H_

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

struct Vector {
	size_t elem_size;
	int capacity;
	int size;
	void* data;
};

enum ImportantVals {
	WRONG_VALUE	=	0xFEDAFEDA
};

struct Vector*		Vector_ctr      (size_t capacity, size_t elem_size);
struct Vector*		Vector_dtr		(struct Vector* vector);
void				Vector_clr		(struct Vector* vector);

int					Vector_push     (struct Vector* vector, void* elem);
int 				Vector_pop      (struct Vector* vector);
int 				Vector_top		(struct Vector* vector);
int 				Vector_ind		(struct Vector* vector, int ind);

int 				Vector_expand   (struct Vector* vector);
int 				Vector_narrow   (struct Vector* vector);

int 				GetVecSize		(struct Vector* vector);
int 				GetCapacity     (struct Vector* vector);

#endif