#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "aebmrvwnsh"

void help(void);

int main(int argc, char **argv) {
    int opt = 0;
    int stats = 0;
    int selected_options[7] = { 0 };

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            for (int j = 0; j < 7; ++j) {
                selected_options[j] = 1;
            }
            break;
        case 'e': selected_options[0] = 1; break;
        case 'b': selected_options[1] = 1; break;
        case 'm': selected_options[2] = 1; break;
        case 'r': selected_options[3] = 1; break;
        case 'v': selected_options[4] = 1; break;
        case 'w': selected_options[5] = 1; break;
        case 'n': selected_options[6] = 1; break;
        case 's': stats = 1; break;
        case 'h': help(); return 0;
        default: help(); return 0;
        }
    }

    int sum = 0;
    for (int k = 0; k < 7; ++k) {
        sum += selected_options[k];
    }

    if (sum == 0) {
        help();
        return 0;
    }

    if (selected_options[0]) {

        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, M_E - e());
        if (stats) {
            printf("e() terms = %d\n", e_terms());
        }
    }

    if (selected_options[1]) {
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
            M_PI - pi_bbp());
        if (stats) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }

    if (selected_options[2]) {
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            M_PI - pi_madhava());
        if (stats) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }

    if (selected_options[3]) {
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
            M_PI - pi_euler());
        if (stats) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }

    if (selected_options[4]) {
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
            M_PI - pi_viete());
        if (stats) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }

    if (selected_options[5]) {
        printf("pi_wallis() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_wallis(), M_PI,
            M_PI - pi_wallis());
        if (stats) {
            printf("pi_wallis() terms = %d\n", pi_wallis_factors());
        }
    }

    if (selected_options[6]) {
        double i = 0.0;
        while (i <= 9.9) {
            printf("sqrt_newton(%.2lf) = %16.15lf, sqrt(%.2lf) = %16.15lf, diff = %16.15lf\n", i,
                sqrt_newton(i), i, sqrt(i), sqrt(i) - sqrt_newton(i));
            if (stats) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }

            i = i + 0.1;
        }
    }

    return 0;
}

void help(void) {
    printf("%s\n",
        "SYNOPSIS\n   A test harness for the small numerical library.\nUSAGE\n   "
        "./mathlib-test-x86 -[aebmrvnsh]\n\nOPTIONS\n  -a   Runs all tests.\n  -e   Runs e test.\n "
        " -b   Runs BBP pi test.\n  -m   Runs Madhava pi test.\n  -r   Runs Euler pi test.\n  -v   "
        "Runs Viete pi test.\n  -w   Runs Wallis pi test.\n  -n   Runs Newton square root tests.\n "
        " -s   Print verbose statistics.\n  -h   Display program synopsis and usage.");
}
