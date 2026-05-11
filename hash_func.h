#ifndef _HASH_FUNC_H_
#define _HASH_FUNC_H_

#include <stdint.h>
#include <string.h>

#define TABLE_SIZE  1000
#define BIT_MUL     0x45d9f3b
#define KNUTH_MUL   2654435769u
#define CRC32_MUL   0xedb88320

union float_int {
    float f;
    uint32_t u;
};

void		save_to_csv			(const char* filename, uint32_t* cnt)	;
void		run_int_tests		()										;
void		run_float_tests		()										;
void		run_string_tests	()										;

uint32_t	hash_int_mod		(uint32_t x)							;
uint32_t	hash_int_bit		(uint32_t x)							;
uint32_t	hash_int_knuth		(uint32_t x)							;
uint32_t	hash_float_cast_bit	(float f)								;
uint32_t	hash_float_bits		(float f)								;
uint32_t	hash_float_mantissa	(float f)								;
uint32_t	hash_float_exponent	(float f)								;
uint32_t	hash_float_mul_me	(float f)								;
uint32_t	hash_str_len		(const char* s)							;
uint32_t	hash_str_sum		(const char* s)							;
uint32_t	hash_str_poly		(const char* s)							;
uint32_t	hash_str_crc32		(const char* s)							;
void        gen_crc32_table		()										;

#endif