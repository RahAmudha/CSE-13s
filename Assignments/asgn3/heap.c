#include "heap.h"

void fix_heap(Stats *stats, uint32_t *arr, uint32_t first, uint32_t last);
uint32_t max_child(Stats *stats, uint32_t *arr, uint32_t first, uint32_t last);

void heap_sort(Stats *stats, uint32_t *arr, uint32_t len) {
    uint32_t first = 1;
    uint32_t last = len;
    for (uint32_t t = last / 2; t > first - 1; --t) {
        fix_heap(stats, arr, t, last);
    }
    for (uint32_t l = last; l > first; --l) {
        swap(stats, &arr[first - 1], &arr[l - 1]);
        fix_heap(stats, arr, first, l - 1);
    }
}

void fix_heap(Stats *stats, uint32_t *arr, uint32_t first, uint32_t last) {
    uint32_t found = 0;
    uint32_t parent = first;
    uint32_t great = max_child(stats, arr, parent, last);
    while (parent <= last / 2 && !found) {
        if (cmp(stats, arr[parent - 1], arr[great - 1]) < 0) {
            swap(stats, &arr[parent - 1], &arr[great - 1]);
            parent = great;
            great = max_child(stats, arr, parent, last);
        } else {
            found = 1;
        }
    }
}

uint32_t max_child(Stats *stats, uint32_t *arr, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if (right <= last && cmp(stats, arr[right - 1], arr[left - 1]) > 0) {
        return right;
    }
    return left;
}
