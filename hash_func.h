#ifndef _HASH_FUNC_H_
#define _HASH_FUNC_H_

#include <stdint.h>
#include <string.h>

#define ui unsigned int
#define TABLE_SIZE  1000
#define BIT_MUL     0x45d9f3b
#define KNUTH_MUL   2654435769u
#define CRC32_MUL   0xedb88320

static ui hash_int_mod(ui x) {
    return x % TABLE_SIZE;
}

static ui hash_int_bit(ui x) {
    x = ((x >> 16) ^ x) * BIT_MUL;
    x = ((x >> 16) ^ x) * BIT_MUL;
    x = (x >> 16) ^ x;
    return x % TABLE_SIZE;
}

static ui hash_int_knuth(ui x) {
    return (ui)(x * KNUTH_MUL) % TABLE_SIZE;
}

union float_int {    // float size = unsigned int size = 32 bit
    float f;
    ui u;
};

static ui hash_float_cast_bit(float f) {
    int x = (int)f;
    union float_int fu; 
    fu.f = (float)x; 
    return fu.u % TABLE_SIZE;
}

static ui hash_float_bits(float f) {
    union float_int fu;
    fu.f = f;
    return fu.u % TABLE_SIZE;
}

static ui hash_float_mantissa(float f) {
    union float_int fu; 
    fu.f = f;
    return (fu.u & 0x7fffffu) % TABLE_SIZE;
}

static ui hash_float_exponent(float f) {
    union float_int fu;
    fu.f = f;
    return ((fu.u >> 23) & 0xffu) % TABLE_SIZE;
}

static ui hash_float_mul_me(float f) {
    union float_int fu; 
    fu.f = f;
    ui m = (fu.u & 0x7fffffu);
    ui e = ((fu.u >> 23) & 0xffu);
    return (m * e) % TABLE_SIZE;
}

static ui hash_str_len(const char* s) {
    return (ui)strlen(s) % TABLE_SIZE;
}

static ui hash_str_sum(const char* s) {
    ui sum = 0;
    while (*s) 
        sum += (unsigned char)(*s++);

    return sum % TABLE_SIZE;
}

static ui hash_str_poly(const char* s) {
    ui hash = 0;
    ui p = 31;
    while (*s) 
        hash = hash * p + (unsigned char)(*s++);

    return hash % TABLE_SIZE;
}

ui crc32_table[256];

static void gen_crc32_table() {
    for (ui i = 0; i < 256; ++i) {
        ui ch = i;
        for (size_t j = 0; j < 8; ++j) {
            if (ch & 1) ch = (ch >> 1) ^ CRC32_MUL;
            else ch >>= 1;
        }

        crc32_table[i] = ch;
    }
}

static ui hash_str_crc32(const char* s) {
    gen_crc32_table();

    ui crc = 0xffffffff;
    while (*s)
        crc = (crc << 8) ^ crc32_table[((crc >> 24) ^ *s++) & 255];

    return crc % TABLE_SIZE;
}

#endif