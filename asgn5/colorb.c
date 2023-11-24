#include "bmp.h"
#include "io.h"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "i:o:h"

void print_help(void);

int main(int argc, char **argv) {
    char *input_name = "";
    char *output_name = "";
    Buffer *in;
    Buffer *out;
    BMP *bitmap;
    char ch;

    while ((ch = getopt(argc, argv, OPTIONS)) != -1) {
        switch (ch) {
        case 'i': input_name = optarg; break;
        case 'o': output_name = optarg; break;
        case 'h': print_help(); return 0;
        }
    }
    if (strcmp(input_name, "") == 0 || strcmp(output_name, "") == 0) {
        fprintf(stderr, "colorb:   no input or output file given.");
        exit(0);
    }
    in = read_open(input_name);
    out = write_open(output_name);
    bitmap = bmp_create(in);
    bmp_reduce_palette(bitmap);
    bmp_write(bitmap, out);
    read_close(&in);
    write_close(&out);
    bmp_free(&bitmap);

    return 0;
}

void print_help(void) {
    printf("Usage: colorb -i infile -o outfile\n       colorb -h\n");
}
