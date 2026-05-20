#include "hash_table_lin.h"

uint32_t linear_probe(uint32_t last_hash, int step_ind, int size) {
	return (last_hash + 1) % size;
}

OpenTable* LinTableCtor(int size, float lf) {
	OpenTable* table = OpenTableCtor(size, lf);

	table->probe = linear_probe;

	return table;
}
