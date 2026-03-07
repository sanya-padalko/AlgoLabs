#ifndef _STACK_VECTOR_H_
#define _STACK_VECTOR_H_

#include "../vector/vector.h"

struct StackVector {
	struct Vector* vector;
};

struct StackVector* StackVector_ctr     (size_t size, size_t elem_size);
struct StackVector*	StackVector_dtr		(struct StackVector* stackvec);
void				StackVector_clr		(struct StackVector* stackvec);

int 				StackVector_push	(struct StackVector* stackvec, void* elem);
int					StackVector_pop		(struct StackVector* stackvec);
int					StackVector_top		(struct StackVector* stackvec);

#endif