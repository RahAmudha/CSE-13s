#include "path.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(capacity);
    p->total_weight = 0;
    return p;
}

void path_free(Path **pp) {
    if (pp != NULL) {
        if (*pp != NULL) {
            stack_free(&((*pp)->vertices));
        }
        free(*pp);
    }
    if (pp != NULL)
        *pp = NULL;
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    uint32_t res = 0;
    if (stack_peek(p->vertices, &res)) {
        p->total_weight += graph_get_weight(g, res, val);
    }
    if (stack_push(p->vertices, val)) {
    }
}

uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t pop = 0;
    uint32_t last = 0;
    if (stack_pop(p->vertices, &pop)) {
        if (stack_peek(p->vertices, &last)) {
            p->total_weight -= graph_get_weight(g, pop, last);
        }
        return pop;
    }
    return 0;
}

void path_copy(Path *dst, const Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->total_weight = src->total_weight;
}

void path_print(const Path *p, FILE *f, const Graph *g) {
    stack_print(p->vertices, f, graph_get_names(g));
}
