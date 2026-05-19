#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hash_func.h"

const int   KEYS_CNT = 1000000;
uint32_t    crc32_table[256];

#ifndef LOAD_TEST

int main() {
    run_int_tests();
    run_float_tests();
    run_string_tests();
}

#endif

void save_to_csv(const char* filename, uint32_t* cnt) {
    FILE* f = fopen(filename, "w");
    for (int i = 0; i < TABLE_SIZE; ++i) 
        fprintf(f, "%d,%u\n", i, cnt[i]);

    fclose(f);
}

void run_int_tests() {
    printf("\n---   INT testing   ---\n");
    uint32_t *data = malloc(KEYS_CNT * sizeof(uint32_t));
    FILE *f_in = fopen("tests/tests_int.txt", "r");
    
    for (int i = 0; i < KEYS_CNT; ++i) 
        fscanf(f_in, "%u", &data[i]);

    fclose(f_in);

    const char* names[] = {"int_mod",     "int_bit",     "int_knuth"};
    uint32_t (*funcs[])(uint32_t)   = {hash_int_mod,  hash_int_bit,  hash_int_knuth};

    for (int f = 0; f < 3; ++f) {
        uint32_t cnt[TABLE_SIZE] = {0};
        clock_t start = clock();
        for (int i = 0; i < KEYS_CNT; ++i) {
            cnt[funcs[f](data[i])]++;
        }
        clock_t end = clock();
        printf("%-10s | Time: %.4f s\n", names[f], (double)(end - start) / CLOCKS_PER_SEC);
        
        char filename[50];
        snprintf(filename, sizeof(filename), "results/%s.csv", names[f]);
        save_to_csv(filename, cnt);
    }

    free(data);
    printf("--- End INT Testing ---\n");
}

void run_float_tests() {
    printf("\n---   FLOAT testing   ---\n");
    float *data = malloc(KEYS_CNT * sizeof(float));
    FILE *f_in = fopen("tests/tests_float.txt", "r");
    
    for (int i = 0; i < KEYS_CNT; ++i) 
        fscanf(f_in, "%f", &data[i]);

    fclose(f_in);

    const char* names[] =  {"fl_intbit",         "fl_bits",       "fl_mant",            "fl_exp",            "fl_mul_me"};
    uint32_t (*funcs[])(float) = {hash_float_cast_bit, hash_float_bits, hash_float_mantissa,  hash_float_exponent, hash_float_mul_me};

    for (int f = 0; f < 5; ++f) {
        uint32_t cnt[TABLE_SIZE] = {0};
        clock_t start = clock();
        for (int i = 0; i < KEYS_CNT; ++i)
            ++cnt[funcs[f](data[i])];

        clock_t end = clock();
        printf("%-10s | Time: %.4f s\n", names[f], (double)(end - start) / CLOCKS_PER_SEC);
        
        char filename[50];
        snprintf(filename, sizeof(filename), "results/%s.csv", names[f]);
        save_to_csv(filename, cnt);
    }
    free(data);
    printf("--- End FLOAT Testing ---\n");
}

void run_string_tests() {
    printf("\n---   STRING testing   ---\n");
    char (*data)[21] = malloc(KEYS_CNT * 21);
    FILE *f_in = fopen("tests/tests_string.txt", "r");
    
    for (int i = 0; i < KEYS_CNT; ++i) 
        fscanf(f_in, "%20s", data[i]);

    fclose(f_in);

    const char* names[] =        {"str_len",    "str_sum",    "str_poly",    "str_crc32"};
    uint32_t (*funcs[])(const char*) = {hash_str_len, hash_str_sum, hash_str_poly, hash_str_crc32};

    for (int f = 0; f < 4; ++f) {
        uint32_t cnt[TABLE_SIZE] = {0};
        clock_t start = clock();
        for (int i = 0; i < KEYS_CNT; ++i) {
            cnt[funcs[f](data[i])]++;
        }
        clock_t end = clock();
        printf("%-10s | Time: %.4f s\n", names[f], (double)(end - start) / CLOCKS_PER_SEC);
        
        char filename[50];
        snprintf(filename, sizeof(filename), "results/%s.csv", names[f]);
        save_to_csv(filename, cnt);
    }
    free(data);
    printf("--- End STRING Testing ---\n");
}


uint32_t hash_int_mod(uint32_t x) {
    return x % TABLE_SIZE;
}

uint32_t hash_int_bit(uint32_t x) {
    x = ((x >> 16) ^ x) * BIT_MUL;
    x = ((x >> 16) ^ x) * BIT_MUL;
    x = (x >> 16) ^ x;
    return x % TABLE_SIZE;
}

uint32_t hash_int_knuth(uint32_t x) {
    return (uint32_t)(x * KNUTH_MUL) % TABLE_SIZE;
}

uint32_t hash_float_cast_bit(float f) {
    int x = (int)f;
    union float_int fu; 
    fu.f = (float)x; 
    return fu.u % TABLE_SIZE;
}

uint32_t hash_float_bits(float f) {
    union float_int fu;
    fu.f = f;
    return fu.u % TABLE_SIZE;
}

uint32_t hash_float_mantissa(float f) {
    union float_int fu; 
    fu.f = f;
    return (fu.u & 0x7fffffu) % TABLE_SIZE;
}

uint32_t hash_float_exponent(float f) {
    union float_int fu;
    fu.f = f;
    return ((fu.u >> 23) & 0xffu) % TABLE_SIZE;
}

uint32_t hash_float_mul_me(float f) {
    union float_int fu; 
    fu.f = f;
    uint32_t m = (fu.u & 0x7fffffu);
    uint32_t e = ((fu.u >> 23) & 0xffu);
    return (m * e) % TABLE_SIZE;
}

uint32_t hash_str_len(const char* s) {
    return (uint32_t)strlen(s) % TABLE_SIZE;
}

uint32_t hash_str_sum(const char* s) {
    uint32_t sum = 0;
    while (*s) 
        sum += (unsigned char)(*s++);

    return sum % TABLE_SIZE;
}

uint32_t hash_str_poly(const char* s) {
    uint32_t hash = 0;
    uint32_t p = 31;
    while (*s) 
        hash = hash * p + (unsigned char)(*s++);

    return hash % TABLE_SIZE;
}

uint32_t hash_str_crc32(const char* s) {
    gen_crc32_table();

    uint32_t crc = 0xffffffff;
    while (*s)
        crc = (crc << 8) ^ crc32_table[((crc >> 24) ^ *s++) & 255];

    return crc % TABLE_SIZE;
}

void gen_crc32_table() {
    for (uint32_t i = 0; i < 256; ++i) {
        uint32_t ch = i;
        for (size_t j = 0; j < 8; ++j) {
            if (ch & 1) ch = (ch >> 1) ^ CRC32_MUL;
            else ch >>= 1;
        }

        crc32_table[i] = ch;
    }
}
