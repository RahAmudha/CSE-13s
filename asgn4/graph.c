#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graph {
    uint32_t vertices;
    bool directed;
    bool *visited;
    char **names;
    uint32_t **weights;
} Graph;

Graph *graph_create(uint32_t vertices, bool directed) {
    Graph *g = calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;
    g->visited = calloc(vertices, sizeof(bool));
    g->names = calloc(vertices, sizeof(char *));
    g->weights = calloc(vertices, sizeof(g->weights[0]));
    for (uint32_t i = 0; i < vertices; ++i) {
        g->weights[i] = calloc(vertices, sizeof(g->weights[0][0]));
    }
    return g;
}

void graph_free(Graph **gp) {
    if (gp != NULL && *gp != NULL) {
        if ((*gp)->visited) {
            free((*gp)->visited);
            (*gp)->visited = NULL;
        }
        if ((*gp)->names) {
            for (uint32_t v = 0; v < (*gp)->vertices; ++v) {
                free((*gp)->names[v]);
            }
            free((*gp)->names);
            (*gp)->names = NULL;
        }
        if ((*gp)->weights) {
            for (uint32_t v = 0; v < (*gp)->vertices; ++v) {
                free((*gp)->weights[v]);
            }
            free((*gp)->weights);
        }
        free(*gp);
    }
    if (gp != NULL) {
        *gp = NULL;
    }
}

char **graph_get_names(const Graph *g) {
    return g->names;
}

uint32_t graph_vertices(const Graph *g) {
    return g->vertices;
}

void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    if (g->names[v])
        free(g->names[v]);
    g->names[v] = strdup(name);
}

const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    return g->names[v];
}

void graph_visit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = true;
}

void graph_unvisit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = false;
}

bool graph_visited(const Graph *g, uint32_t v) {
    return g->visited[v];
}

void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    if (!g->directed) {
        g->weights[end][start] = weight;
    }
    g->weights[start][end] = weight;
}

uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    return g->weights[start][end];
}

void graph_print(const Graph *g) {
    for (uint32_t c = 0; c < g->vertices; ++c) {
        for (uint32_t r = 0; r < g->vertices; ++r) {
            if (graph_get_weight(g, c, r))
                printf("%s to %s, w: %d\n", graph_get_vertex_name(g, c),
                    graph_get_vertex_name(g, r), graph_get_weight(g, c, r));
        }
    }
}
