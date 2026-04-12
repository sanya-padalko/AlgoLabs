#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hash_func.h"

const int KEYS_CNT = 1000000;

void save_to_csv(const char* filename, ui* cnt) {
    FILE* f = fopen(filename, "w");
    for (int i = 0; i < TABLE_SIZE; ++i) 
        fprintf(f, "%d,%u\n", i, cnt[i]);

    fclose(f);
}

void run_int_tests() {
    printf("\n---   INT testing   ---\n");
    ui *data = malloc(KEYS_CNT * sizeof(ui));
    FILE *f_in = fopen("tests/tests_int.txt", "r");
    
    for (int i = 0; i < KEYS_CNT; ++i) 
        fscanf(f_in, "%u", &data[i]);

    fclose(f_in);

    const char* names[] = {"int_mod",     "int_bit",     "int_knuth"};
    ui (*funcs[])(ui)   = {hash_int_mod,  hash_int_bit,  hash_int_knuth};

    for (int f = 0; f < 3; ++f) {
        ui cnt[TABLE_SIZE] = {0};
        clock_t start = clock();
        for (int i = 0; i < KEYS_CNT; ++i) {
            cnt[funcs[f](data[i])]++;
        }
        clock_t end = clock();
        printf("%-10s | Time: %.4f s\n", names[f], (double)(end - start) / CLOCKS_PER_SEC);
        
        char filename[50];
        sprintf(filename, "results/%s.csv", names[f]);
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
    ui (*funcs[])(float) = {hash_float_cast_bit, hash_float_bits, hash_float_mantissa,  hash_float_exponent, hash_float_mul_me};

    for (int f = 0; f < 5; ++f) {
        ui cnt[TABLE_SIZE] = {0};
        clock_t start = clock();
        for (int i = 0; i < KEYS_CNT; ++i)
            ++cnt[funcs[f](data[i])];

        clock_t end = clock();
        printf("%-10s | Time: %.4f s\n", names[f], (double)(end - start) / CLOCKS_PER_SEC);
        
        char filename[50];
        sprintf(filename, "results/%s.csv", names[f]);
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
    ui (*funcs[])(const char*) = {hash_str_len, hash_str_sum, hash_str_poly, hash_str_crc32};

    for (int f = 0; f < 4; ++f) {
        ui cnt[TABLE_SIZE] = {0};
        clock_t start = clock();
        for (int i = 0; i < KEYS_CNT; ++i) {
            cnt[funcs[f](data[i])]++;
        }
        clock_t end = clock();
        printf("%-10s | Time: %.4f s\n", names[f], (double)(end - start) / CLOCKS_PER_SEC);
        
        char filename[50];
        sprintf(filename, "results/%s.csv", names[f]);
        save_to_csv(filename, cnt);
    }
    free(data);
    printf("--- End STRING Testing ---\n");
}

int main() {
    run_int_tests();
    run_float_tests();
    run_string_tests();
}