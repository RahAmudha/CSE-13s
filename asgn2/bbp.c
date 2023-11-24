#include "mathlib.h"

static int bbpcnt;
double pi_bbp(void) {
    double sum = 0.0;
    double term = 1.0;
    double num1 = 1.0;
    double den1 = 1.0;
    double den2 = 1.0 / 16.0;
    for (bbpcnt = 0; absolute(term) >= EPSILON; ++bbpcnt) {
        num1 = bbpcnt * (120.0 * bbpcnt + 151.0) + 47.0;
        den1 = bbpcnt * (bbpcnt * (bbpcnt * (512.0 * bbpcnt + 1024.0) + 712.0) + 194.0) + 15.0;
        den2 *= 16.0;
        term = num1 / (den1 * den2);
        sum += term;
    }
    return sum;
}

int pi_bbp_terms(void) {
    return bbpcnt;
}
