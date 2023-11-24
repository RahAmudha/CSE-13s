#include "mathlib.h"

static int vtcnt;
double pi_viete(void) {
    double prod = 1.0;
    double factor = 0.0;
    double num1 = 0.0;
    double den1 = 2.0;
    for (vtcnt = 1; absolute(1 - factor) >= EPSILON; ++vtcnt) {
        num1 = sqrt_newton(2 + num1);
        factor = num1 / den1;
        prod *= factor;
    }
    prod = 2 / prod;
    return prod;
}

int pi_viete_factors(void) {
    return vtcnt - 1;
}
