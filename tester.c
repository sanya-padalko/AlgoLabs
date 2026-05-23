#include "testing.h"
#include <string.h>
#include <stdlib.h>
#include "small-sortings.h"
#include "heap-sortings.h"
#include "merge-sortings.h"
#include "part-sortings.h"
#include "hoar-shell.h"
#include "intro-sort.h"
#include "not-comp-sorts.h"
#include "base-quick-sort.h"

void SaveResults(double* time_result, const char* sort_file_name, int res_cnt) {
    FILE* res_file = fopen(sort_file_name, "w");

    for (int ind = 0; ind < res_cnt; ++ind)
        fprintf(res_file, "%lg\n", time_result[ind]);

    fclose(res_file);
}

void Part1() { // bubble, insertion, selection, shell's sortings
    SaveResults(Test("small_tests/", Bubble_sort, 0, 1000, 50), "part1/bubble",     21);
    printf("Bubble sort counted\n");
    SaveResults(Test("small_tests/", Insert_sort, 0, 1000, 50), "part1/insertion",  21);
    printf("Insertion sort counted\n");
    SaveResults(Test("small_tests/", Select_sort, 0, 1000, 50), "part1/selection",  21);
    printf("Selection sort counted\n");
    SaveResults(Test("small_tests/", Shell_sort,  0, 1000, 50), "part1/shell",      21);
    printf("Shell sort counted\n");

    SaveResults(Test("small_tests/", OrigShell_sort,  0, 1000, 50), "part1/orig-shell",     21);
    printf("Original Shell sort counted\n");
    SaveResults(Test("small_tests/", PrattShell_sort,  0, 1000, 50), "part1/pratt-shell",   21);
    printf("Pratt\'s Shell sort counted\n");
    SaveResults(Test("small_tests/", CiuraShell_sort,  0, 1000, 50), "part1/ciura-shell",   21);
    printf("Ciura\'s Shell sort counted\n");
    SaveResults(Test("small_tests/", GonnetShell_sort,  0, 1000, 50), "part1/gonnet-shell", 21);
    printf("Gonnet\'s Shell sort counted\n");    
}

void Part2() { // bottom-up heap-sort
    for (int heap_k = 2; heap_k <= 10; ++heap_k) {
        char* heap_file_name = (char*)calloc(20, sizeof(char));
        sprintf(heap_file_name, "part2/heap-%d", heap_k);

        K_HEAP = heap_k;
        SaveResults(Test("big_tests/", Bottom_up_heap_sort, 0, 1000000, 10000), heap_file_name, 100);
        printf("Heap with %d sons counted\n", heap_k);
    }
}

void Part3() { // merge sortings
    SaveResults(Test("big_tests/", GoRecMerge_sort, 0, 1000000, 10000), "part3/rec-merge",  100);
    printf("Recursive merge sort counted\n");
    SaveResults(Test("big_tests/", IterMerge_sort, 0, 1000000, 10000), "part3/iter-merge",  100);
    printf("Iterative merge sort counted\n");
}

void Part4() { //quick sortings
    hoar_pivot = pivot_central;

    SaveResults(Test("test_most_dublicates/", Hoar_sort, 0, 1000000, 10000), "part4/hoar-dub",  100);
    printf("Hoar's sort on dub tests counted\n");
    return;
    SaveResults(Test("test_most_dublicates/", Lomuto_sort, 0, 750000, 10000), "part4/lomut-dub",  75);
    printf("Lomuto's sort on dub tests counted\n");
    return;
    SaveResults(Test("test_most_dublicates/", Thick_sort, 0, 1000000, 10000), "part4/thick-dub",  100);
    printf("Thick sort on dub tests counted\n");
    return;
    SaveResults(Test("big_tests/", Thick_sort, 0, 1000000, 10000), "part4/thick-big",  100);
    printf("Thick sort on big tests counted\n");
    return;
    SaveResults(Test("big_tests/", Hoar_sort, 0, 1000000, 10000), "part4/hoar-big",  100);
    printf("Hoar's sort on big tests counted\n");
    return;
    SaveResults(Test("big_tests/", Lomuto_sort, 0, 1000000, 10000), "part4/lomut-big",  100);
    printf("Lomuto's sort on big tests counted\n");
    return;
}

void Part5() { // hoar's sort with different pivots
    hoar_pivot = pivot_random_med;
    SaveResults(Test("big_tests/", Hoar_sort, 0, 1000000, 10000), "part5/hoar-random-med",  100);
    printf("Hoar's with pivot = mediana of three random counted\n");
    hoar_pivot = pivot_mediana3;
    SaveResults(Test("big_tests/", Hoar_sort, 0, 1000000, 10000), "part5/hoar-mediana3",  100);
    printf("Hoar's with pivot = mediana 3 counted\n");
    hoar_pivot = pivot_central;
    SaveResults(Test("big_tests/", Hoar_sort, 0, 1000000, 10000), "part5/hoar-central",  100);
    printf("Hoar's with pivot = central counted\n");
    hoar_pivot = pivot_random;
    SaveResults(Test("big_tests/", Hoar_sort, 0, 1000000, 10000), "part5/hoar-random",  100);
    printf("Hoar's with pivot = random counted\n");
}

void Part6() { // hoar's sort with shell sort on small segments
    for (int ind = 1; ind <= 512; ind *= 2) {
        block_size = ind;
        char* data_file = (char*)calloc(30, sizeof(char));
        sprintf(data_file, "part6/hoar-shell-%d", block_size);

        SaveResults(Test("big_tests/", HoarShell_sort, 0, 1000000, 10000), data_file,  100);
        printf("Block size = %d counted\n", block_size);
    }
}

void Part7() { // introsort with different heap's deeps
    for (int ind = 1; ind <= 16; ind *= 2) {
        max_deep = ind;
        char* intro_file_name = (char*)calloc(40, sizeof(char));
        sprintf(intro_file_name, "part7/intro-heap-%d", max_deep);
        
        SaveResults(Test("big_tests/", Intro_sort, 0, 1000000, 10000), intro_file_name,  100);
        printf("Intro sort with heap's deep = %dlog n counted\n", max_deep);
    }

    max_deep = 8;
    SaveResults(Test("big_tests/", Hoar_sort, 0, 1000000, 10000), "part7/best-quick",  100);
    printf("Best quick sort counted\n");
    SaveResults(Test("big_tests/", Intro_sort, 0, 1000000, 10000), "part7/intro-sort",  100);
    printf("Intro sort counted\n");
}

void Part9() { // LSD, MSD sortings
    SaveResults(Test("big_tests/", LSD_sort, 0, 1000000, 10000), "part9/lsd-sort",  100);
    printf("LSD sort counted\n");
    SaveResults(Test("big_tests/", MSD_sort, 0, 1000000, 10000), "part9/msd-sort",  100);
    printf("MSD sort counted\n");
}

void Part10() { // best sortings of all parts
    SaveResults(Test("big_tests/", BaseQuick_sort, 0, 1000000, 10000), "part10/quick-sort",  100);
    printf("Base quick sort counted\n");
    SaveResults(Test("big_tests/", Shell_sort, 0, 1000000, 10000), "part10/shell-sort",  100);
    printf("Shell sort counted\n");
    K_HEAP = 4;
    SaveResults(Test("big_tests/", Bottom_up_heap_sort, 0, 1000000, 10000), "part10/heap-sort",  100);
    printf("Heap sort counted\n");
    SaveResults(Test("big_tests/", IterMerge_sort, 0, 1000000, 10000), "part10/merge-sort",  100);
    printf("Iterative merge sort counted\n");
    SaveResults(Test("big_tests/", HoarShell_sort, 0, 1000000, 10000), "part10/hoar-sort",  100);
    printf("Hoar\'s sort counted\n");
    max_deep = 8;
    SaveResults(Test("big_tests/", Intro_sort, 0, 1000000, 10000), "part10/intro-sort",  100);
    printf("Intro sort counted\n");
    SaveResults(Test("big_tests/", LSD_sort, 0, 1000000, 10000), "part10/lsd-sort",  100);
    printf("LSD sort counted\n");
}

int main(int argc, char* argv[]) {
	srand(42);

    int part_number = 0;
    if (argc > 1)
        part_number = argv[1][0] - '0';

    switch (part_number) {
        case 1:
            Part1();
            break;

        case 2:
            Part2();
            break;

        case 3:
            Part3();
            break;

        case 4:
            Part4();
            break;

        case 5:
            Part5();
            break;

        case 6:
            Part6();
            break;

        case 7:
            Part7();
            break;

        case 9:
            Part9();
            break;

        default:
            Part10();
    }

}