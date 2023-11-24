#include "mathlib.h"

static int mdhvcnt;
double pi_madhava(void) {
    mdhvcnt = 0;
    double term = 1.0;
    double sum = 0.0;
    double den1 = 1.0;
    double den2 = 1.0;
    while (absolute(term) >= EPSILON) {
        term = 1 / (den1 * den2);
        den1 *= -3.0;
        den2 += 2.0;
        sum += term;
        mdhvcnt += 1;
    }
    sum *= sqrt_newton(12.0);
    return sum;
}

int pi_madhava_terms(void) {
    return mdhvcnt;
}
