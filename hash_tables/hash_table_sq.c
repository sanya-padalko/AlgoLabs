#include "hash_table_sq.h"

uint32_t square_probe(uint32_t last_hash, int step_ind, int size) {
	return (last_hash + step_ind * step_ind) % size;
}

OpenTable* SqTableCtor(int size, float lf) {
	OpenTable* table = OpenTableCtor(size, lf);

	table->probe = square_probe;

	return table;
}
