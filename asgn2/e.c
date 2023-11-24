#include "mathlib.h"

static int ecnt;
double e(void) {
    double sum = 0.0;
    double term = 1.0;
    double den1 = 1.0;
    for (ecnt = 1; absolute(term) >= EPSILON; ++ecnt) {
        sum += term;
        den1 *= ecnt;
        term = 1.0 / den1;
    }
    return sum;
}

int e_terms(void) {
    ecnt--;
    return ecnt;
}
