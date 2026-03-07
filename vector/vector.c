#include "vector.h"

struct Vector* Vector_ctr(size_t capacity, size_t elem_size) {
	if (capacity < 0)   return NULL;

	struct Vector* vector = (struct Vector*)calloc(1, sizeof(struct Vector));
	if (!vector)		return NULL;

	vector->elem_size = elem_size;
	vector->capacity = capacity;
	vector->size = 0;
	vector->data = calloc(capacity, elem_size);
	if (!vector->data)  return NULL;

	return vector;
}

struct Vector* Vector_dtr(struct Vector* vector) {
	if (!vector)   return NULL;

	Vector_clr(vector);
	vector->elem_size = vector->capacity = 0;
	free(vector->data);

	free(vector);
	return NULL;
}

void Vector_clr(struct Vector* vector) {
	if (!vector)	return ;

	vector->size = 0;
}

int Vector_push(struct Vector* vector, void* elem) {
	if (!vector)		return 0;
	if (!vector->data)  return 0;
	if (!elem)			return 0;

	if (GetCapacity(vector) == GetVecSize(vector)) {
		int expand_res = Vector_expand(vector);
		if (!expand_res) return 0;
	}

	memcpy(vector->data + vector->elem_size * GetVecSize(vector), elem, vector->elem_size);
	++vector->size;
	return 1;
}

int Vector_pop(struct Vector* vector) {
	if (!vector)					return WRONG_VALUE;
	if (!vector->data)				return WRONG_VALUE;
	if (GetVecSize(vector) <= 0)	return WRONG_VALUE;

	int val = Vector_ind(vector, GetVecSize(vector) - 1);

	if (GetVecSize(vector) * 4 <= GetCapacity(vector)) {
		int narrow_res = Vector_narrow(vector);
		if (!narrow_res)			return WRONG_VALUE;
	}

	--vector->size;
	return val;
}

int Vector_top(struct Vector* vector) {
	if (!vector)				return WRONG_VALUE;
	if (!vector->data)			return WRONG_VALUE;
	if (GetVecSize(vector) <= 0)	return WRONG_VALUE;

	int val = Vector_ind(vector, GetVecSize(vector) - 1);

	return val;
}

int Vector_ind(struct Vector* vector, int ind) {
	if (!vector)				return WRONG_VALUE;
	if (!vector->data)			return WRONG_VALUE;
	if (GetVecSize(vector) <= ind || ind < 0)	return WRONG_VALUE;

	return *(int*)(vector->data + vector->elem_size * ind);
}

int Vector_expand(struct Vector* vector) {
	if (!vector)		return 0;

	vector->capacity *= 2;
	vector->data = realloc(vector->data, vector->elem_size * GetCapacity(vector));
	if (!vector->data)  return 0;
	
	return 1;
}

int Vector_narrow(struct Vector* vector) {
	if (!vector)		return 0;

	vector->capacity /= 4;
	vector->data = realloc(vector->data, vector->elem_size * GetCapacity(vector));
	if (!vector->data)  return 0;

	return 1;
}

int GetVecSize(struct Vector* vector) {
	if (!vector)	return -1;

	return vector->size;
}

int GetCapacity(struct Vector* vector) {
	if (!vector)	return -1;

	return vector->capacity;
}