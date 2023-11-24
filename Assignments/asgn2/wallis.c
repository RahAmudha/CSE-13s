#include "mathlib.h"

static int wllscnt;
double pi_wallis(void) {
    double prod = 1.0;
    double factor = 0.0;
    double num1 = 1.0;
    double den1 = 1.0;
    for (wllscnt = 1; absolute(1 - factor) >= EPSILON; ++wllscnt) {
        num1 = 4.0 * wllscnt * wllscnt;
        den1 = 4.0 * wllscnt * wllscnt - 1.0;
        factor = num1 / den1;
        prod *= factor;
    }
    prod *= 2;
    return prod;
}

int pi_wallis_factors(void) {
    return wllscnt - 1;
}
