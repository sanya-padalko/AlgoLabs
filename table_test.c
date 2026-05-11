#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "hash_tables/hash_table_2h.h"
#include "hash_tables/hash_table_cep.h"
#include "hash_tables/hash_table_kuk.h"
#include "hash_tables/hash_table_lin.h"
#include "hash_tables/hash_table_sq.h"

static double GetTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000.0;
}

uint32_t* test_arr;
float load_fact = 0.48;

void test_2h(int type) {
    
    FILE* res_file;
    if (type == 1)
        res_file = fopen("table_tests/res1_2h", "w");
    else
        res_file = fopen("table_tests/res2_2h", "w");

    for (int size = 10000; size <= 1e6; size += 1e4) {
        OpenTable* ht = OpenTableCtor(2, load_fact);

        FILE* test_file;
        if (type == 1)
            test_file = fopen("table_tests/test1", "r");
        else
            test_file = fopen("table_tests/test2", "r");
        
        double start_time = GetTime();
        for (int i = 0; i < size; ++i) {
            char type;
            uint32_t key;
            fscanf(test_file, "%c %u", &type, &key);

            if (type == 'i')
                DubInsert(ht, key);
            else if (type == 's')
                DubSearch(ht, key);
            else
                DubRemove(ht, key);
        }
        double end_time = GetTime();

        fprintf(stderr, "2h: %d / %d\r", size, (int)1e6);

        fclose(test_file);
        fprintf(res_file, "%lg\n", end_time - start_time);
        free(ht);
    }

    fprintf(stderr, "\n");
}

void test_cep(int type) {
    FILE* res_file;
    if (type == 1)
        res_file = fopen("table_tests/res1_cep", "w");
    else
        res_file = fopen("table_tests/res2_cep", "w");

    for (int size = 10000; size <= 1e6; size += 1e4) {
        CepTable* ht = CepTableCtor(2, load_fact);

        FILE* test_file;
        if (type == 1)
            test_file = fopen("table_tests/test1", "r");
        else
            test_file = fopen("table_tests/test2", "r");
        
        double start_time = GetTime();
        for (int i = 0; i < size; ++i) {
            char type;
            uint32_t key;
            fscanf(test_file, "%c %u", &type, &key);

            if (type == 'i')
                CepInsert(ht, key);
            else if (type == 's')
                CepSearch(ht, key);
            else
                CepRemove(ht, key);
        }
        double end_time = GetTime();

        fprintf(stderr, "Cep: %d / %d\r", size, (int)1e6);

        fclose(test_file);
        fprintf(res_file, "%lg\n", end_time - start_time);
        free(ht);
    }
    fprintf(stderr, "\n");
}

void test_kuk(int type) {
    FILE* res_file;
    if (type == 1)
        res_file = fopen("table_tests/res1_kuk", "w");
    else
        res_file = fopen("table_tests/res2_kuk", "w");

    for (int size = 10000; size <= 1e6; size += 1e4) {
        OpenTable* ht = OpenTableCtor(2, load_fact);

        FILE* test_file;
        if (type == 1)
            test_file = fopen("table_tests/test1", "r");
        else
            test_file = fopen("table_tests/test2", "r");
        
        double start_time = GetTime();
        for (int i = 0; i < size; ++i) {
            char type;
            uint32_t key;
            fscanf(test_file, "%c %u", &type, &key);

            if (type == 'i')
                KukInsert(ht, key);
            else if (type == 's')
                KukSearch(ht, key);
            else
                KukRemove(ht, key);
        }
        double end_time = GetTime();

        fprintf(stderr, "Kukushka: %d / %d\r", size, (int)1e6);

        fclose(test_file);
        fprintf(res_file, "%lg\n", end_time - start_time);
        free(ht);
    }
    fprintf(stderr, "\n");
}

void test_lin(int type) {
    FILE* res_file;
    if (type == 1)
        res_file = fopen("table_tests/res1_lin", "w");
    else
        res_file = fopen("table_tests/res2_lin", "w");

    for (int size = 10000; size <= 1e6; size += 1e4) {
        OpenTable* ht = OpenTableCtor(2, load_fact);

        FILE* test_file;
        if (type == 1)
            test_file = fopen("table_tests/test1", "r");
        else
            test_file = fopen("table_tests/test2", "r");
        
        double start_time = GetTime();
        for (int i = 0; i < size; ++i) {
            char type;
            uint32_t key;
            fscanf(test_file, "%c %u", &type, &key);

            if (type == 'i')
                LinInsert(ht, key);
            else if (type == 's')
                LinSearch(ht, key);
            else
                LinRemove(ht, key);
        }
        double end_time = GetTime();

        fprintf(stderr, "Linear: %d / %d\r", size, (int)1e6);

        fclose(test_file);
        fprintf(res_file, "%lg\n", end_time - start_time);
        free(ht);
    }
    fprintf(stderr, "\n");
}

void test_sq(int type) {
    FILE* res_file;
    if (type == 1)
        res_file = fopen("table_tests/res1_sq", "w");
    else
        res_file = fopen("table_tests/res2_sq", "w");

    for (int size = 10000; size <= 1e6; size += 1e4) {
        OpenTable* ht = OpenTableCtor(2, load_fact);

        FILE* test_file;
        if (type == 1)
            test_file = fopen("table_tests/test1", "r");
        else
            test_file = fopen("table_tests/test2", "r");
        
        double start_time = GetTime();
        for (int i = 0; i < size; ++i) {
            char type;
            uint32_t key;
            fscanf(test_file, "%c %u", &type, &key);

            if (type == 'i')
                SqInsert(ht, key);
            else if (type == 's')
                SqSearch(ht, key);
            else
                SqRemove(ht, key);
        }
        double end_time = GetTime();

        fprintf(stderr, "Square: %d / %d\r", size, (int)1e6);

        fclose(test_file);
        fprintf(res_file, "%lg\n", end_time - start_time);
        free(ht);
    }
    fprintf(stderr, "\n");
}

int main() {
    test_arr = (uint32_t*)calloc(1e6, sizeof(uint32_t));
    FILE* test_file = fopen("tests/tests_int.txt", "r");
    for (int i = 0; i < 1e6; ++i)
        fscanf(test_file, "%u", &test_arr[i]);
    fclose(test_file);

    test_2h(1);
    test_2h(2);
    test_cep(1);
    test_cep(2);
    test_kuk(1);
    test_kuk(2);
    test_lin(1);
    test_lin(2);
    test_sq(1);
    test_sq(2);
}