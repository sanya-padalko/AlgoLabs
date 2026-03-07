#include "stack_vector.h"

struct StackVector*	StackVector_ctr(size_t size, size_t elem_size) {
    if (size < 0 || elem_size <= 0) return NULL;

    struct StackVector* stackvec = (struct StackVector*)calloc(1, sizeof(struct StackVector*));
    if (!stackvec)  return NULL;

    stackvec->vector = Vector_ctr(size, elem_size);
    return stackvec;
}

struct StackVector*	StackVector_dtr(struct StackVector* stackvec) {
    if (!stackvec) return NULL;

    Vector_dtr(stackvec->vector);

    free(stackvec);
    return NULL;
}

void StackVector_clr(struct StackVector* stackvec) {
	if (!stackvec) return;

	Vector_clr(stackvec->vector);
}

int StackVector_push(struct StackVector* stackvec, void* elem) {
	if (!stackvec) 		return 0;
	if (!elem)			return 0;
	
	int push_result = Vector_push(stackvec->vector, elem);
	if (push_result == WRONG_VALUE)   return 0;

	return 1;
}

int StackVector_pop(struct StackVector* stackvec) {
	if (!stackvec)		return 0;
	
	int pop_result = Vector_pop(stackvec->vector);
	if (pop_result == WRONG_VALUE)	return 0;

	return 1;
}

int StackVector_top(struct StackVector* stackvector) {
	if (!stackvector)	return WRONG_VALUE;

	return Vector_top(stackvector->vector);
}