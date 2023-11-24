#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "aishqbr:n:p:H"

void print_arr(uint32_t *arr, int size, int elements);
void init_arr(uint32_t *arr, uint32_t *temparr, int size);
void print_help(void);

int main(int argc, char *argv[]) {
    int ch;
    enum Values { i, s, h, q, b };
    Stats stats;

    int seed = 13371453;
    int size = 100;
    int elements = 100;

    Set st = set_empty();

    while ((ch = getopt(argc, argv, OPTIONS)) != -1) {
        switch (ch) {
        case 'a': st = set_universal(); break;
        case 'i': st = set_insert(st, i); break;
        case 's': st = set_insert(st, s); break;
        case 'h': st = set_insert(st, h); break;
        case 'q': st = set_insert(st, q); break;
        case 'b': st = set_insert(st, b); break;
        case 'r': seed = strtoull(optarg, NULL, 10); break;
        case 'n': size = strtoull(optarg, NULL, 10); break;
        case 'p': elements = strtoull(optarg, NULL, 10); break;
        case 'H': print_help(); return 0;
        default: print_help(); return 0;
        }
    }

    if (!st) {
        return 0;
    }

    srand(seed);
    uint32_t *arr = malloc(size * sizeof(uint32_t));
    for (int t = 0; t < size; ++t) {
        arr[t] = rand() & 0x3FFFFFFF;
    }

    uint32_t *temparr = malloc(size * sizeof(uint32_t));
    init_arr(temparr, arr, size);

    if (set_member(st, i)) {
        insertion_sort(&stats, arr, size);
        print_stats(&stats, "Insertion Sort", size);
        reset(&stats);
        print_arr(arr, size, elements);
    }
    init_arr(arr, temparr, size);
    if (set_member(st, h)) {
        heap_sort(&stats, arr, size);
        print_stats(&stats, "Heap Sort", size);
        reset(&stats);
        print_arr(arr, size, elements);
    }
    init_arr(arr, temparr, size);
    if (set_member(st, s)) {
        shell_sort(&stats, arr, size);
        print_stats(&stats, "Shell Sort", size);
        reset(&stats);
        print_arr(arr, size, elements);
    }
    init_arr(arr, temparr, size);
    if (set_member(st, q)) {
        quick_sort(&stats, arr, size);
        print_stats(&stats, "Quick Sort", size);
        reset(&stats);
        print_arr(arr, size, elements);
    }
    init_arr(arr, temparr, size);
    if (set_member(st, b)) {
        batcher_sort(&stats, arr, size);
        print_stats(&stats, "Batcher Sort", size);
        reset(&stats);
        print_arr(arr, size, elements);
    }

    free(arr);
    free(temparr);
    return 0;
}

void print_arr(uint32_t *arr, int size, int elements) {
    for (int j = 0; j < elements && j < size; j++) {
        if (j % 5 == 0 && j) {
            printf("\n");
        }
        printf("%13" PRIu32, arr[j]);
    }
    if (elements) {
        printf("\n");
    }
}

void init_arr(uint32_t *arr, uint32_t *temparr, int size) {
    for (int m = 0; m < size; ++m) {
        arr[m] = temparr[m];
    }
}

void print_help(void) {
    printf("SYNOPSIS\n   A collection of comparison-based sorting algorithms.\n\nUSAGE\n   "
           "./sorting-x86 [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\nOPTIONS\n   -H         "
           "     Display program help and usage.\n   -a              Enable all sorts.\n   -h      "
           "        Enable Heap Sort.\n   -b              Enable Batcher Sort.\n   -s              "
           "Enable Shell Sort.\n   -q              Enable Quick Sort.\n   -i              Enable "
           "Insertion Sort.\n   -n length       Specify number of array elements (default: 100).\n "
           "  -p elements     Specify number of elements to print (default: 100).\n   -r seed      "
           "   Specify random seed (default: 13371453).\n");
}
