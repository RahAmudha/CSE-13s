#include "insert.h"

void insertion_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    for (uint32_t k = 1; k < length; ++k) {
        uint32_t j = k;
        uint32_t temp = move(stats, arr[k]);
        while (j > 0 && cmp(stats, temp, arr[j - 1]) < 0) {
            arr[j] = arr[j - 1];
            j = move(stats, j) - 1;
        }
        arr[j] = move(stats, temp);
    }
}
