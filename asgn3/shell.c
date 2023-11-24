#include "shell.h"

#include "gaps.h"

void shell_sort(Stats *stats, uint32_t *arr, uint32_t len) {
    for (uint32_t gap = 0; gap < 142; ++gap) {
        uint32_t g = gaps[gap];
        for (uint32_t i = g; i < len; ++i) {
            uint32_t j = i;
            uint32_t temp = move(stats, arr[i]);
            while (j >= g && cmp(stats, temp, arr[j - g]) < 0) {
                arr[j] = arr[j - g];
                j = move(stats, j);
                j -= g;
            }
            arr[j] = move(stats, temp);
        }
    }
}
