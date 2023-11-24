#include "batcher.h"

void comparator(Stats *stats, uint32_t *arr, uint32_t x, uint32_t y);
uint32_t bit_length(uint32_t b);

void comparator(Stats *stats, uint32_t *arr, uint32_t x, uint32_t y) {
    if (cmp(stats, arr[x], arr[y]) > 0) {
        swap(stats, &arr[x], &arr[y]);
    }
}

uint32_t bit_length(uint32_t b) {
    int c = 0;
    while (b) {
        c++;
        b >>= 1;
    }
    return c;
}

void batcher_sort(Stats *stats, uint32_t *arr, uint32_t len) {
    if (!len)
        return;

    uint32_t n = len;
    uint32_t t = bit_length(n);
    uint32_t p = 1 << (t - 1);

    while (p > 0) {
        uint32_t q = 1 << (t - 1);
        uint32_t r = 0;
        uint32_t d = p;

        while (d > 0) {
            for (uint32_t i = 0; i < n - d; ++i) {
                if ((i & p) == r) {
                    comparator(stats, arr, i, i + d);
                }
            }
            d = q - p;
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
