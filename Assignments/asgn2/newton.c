#include "mathlib.h"

static int nwtncnt;
double sqrt_newton(double x) {
    nwtncnt = 0;
    double next_y = 1.0;
    double y = 0.0;
    while (absolute(next_y - y) >= EPSILON) {
        y = next_y;
        next_y = 0.5 * (y + x / y);
        nwtncnt += 1;
    }
    return next_y;
}

int sqrt_newton_iters(void) {
    return nwtncnt;
}
