#include "mathlib.h"

static int elrcnt;
double pi_euler(void) {
    double sum = 0.0;
    double term = 1.0;
    for (elrcnt = 1; absolute(term) > EPSILON; elrcnt++) {
        term = 1.0 / elrcnt;
        term = term / elrcnt;
        sum += term;
    }
    sum *= 6;
    sum = sqrt_newton(sum);
    return sum;
}

int pi_euler_terms(void) {
    elrcnt--;
    return elrcnt;
}
