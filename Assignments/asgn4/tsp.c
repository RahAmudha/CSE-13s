#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:dh"

void print_help(FILE *f);

void dfs(Graph *g, Path *p, uint32_t v, Path *best_path);

int main(int argc, char **argv) {
    bool directed = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;

    char ch;
    char *input_file;
    char *output_file;
    bool opt_i = false;
    bool opt_o = false;

    while ((ch = getopt(argc, argv, OPTIONS)) != -1) {
        opterr = 0;
        switch (ch) {
        case 'i':
            input_file = optarg;
            opt_i = true;
            break;
        case 'o':
            output_file = optarg;
            opt_o = true;
            break;
        case 'd': directed = true; break;
        case 'h': print_help(stdout); return 0;
        default:
            fprintf(stderr, "tsp:  unknown or poorly formatted option -%c\n", optopt);
            return 0;
        }
    }

    if (opt_i) {
        infile = fopen(input_file, "r");
        if (infile == NULL) {
            fprintf(stderr, "tsp:  error reading input file %s\n", input_file);
            print_help(stdout);
        }
    }

    if (opt_o)
        outfile = fopen(output_file, "w");

    uint32_t num_vertices = 0;
    if (fscanf(infile, "%u\n", &num_vertices) != 1) {
        fprintf(stderr, "tsp:  error reading number of vertices\n");
        if (infile != stdin)
            fclose(infile);
        exit(1);
    }

    Graph *g = graph_create(num_vertices, directed);
    char *name = malloc(sizeof(char) * 69);
    for (uint32_t v = 0; v < num_vertices; ++v) {
        if (fscanf(infile, "%[^\n]\n", name) != 1) {
            fprintf(stderr, "tsp:  error reading vertices\n");
            graph_free(&g);
            if (infile != stdin)
                fclose(infile);
            exit(1);
        }
        graph_add_vertex(g, name, v);
    }

    uint32_t num_edges = 0;
    if (fscanf(infile, "%u\n", &num_edges) != 1) {
        fprintf(stderr, "tsp:  must provide number of edges\n");
        graph_free(&g);
        if (infile != stdin)
            fclose(infile);
        exit(1);
    }

    uint32_t start = 0;
    uint32_t end = 0;
    int32_t weight = 0;

    for (uint32_t e = 0; e < num_edges; ++e) {
        if (fscanf(infile, "%u %u %u", &start, &end, &weight) != 3) {
            fprintf(stderr, "tsp:  error reading edge\n");
            if (infile != stdin)
                fclose(infile);
            graph_free(&g);
            exit(1);
        }
        graph_add_edge(g, start, end, weight);
    }
    if (infile != stdin)
        fclose(infile);
    //graph_print (g);
    Path *p = path_create(num_vertices + 1);
    Path *best_path = path_create(num_vertices + 1);

    dfs(g, p, START_VERTEX, best_path);

    if (path_distance(best_path)) {
        fprintf(outfile, "Alissa starts at:\n");
        path_print(best_path, outfile, g);
        fprintf(outfile, "Total Distance: %u\n", path_distance(best_path));
    } else
        fprintf(outfile, "No path found! Alissa is lost!\n");

    graph_free(&g);
    path_free(&p);
    path_free(&best_path);

    free(name);

    if (outfile != stdout)
        fclose(outfile);
    return 0;
}

void dfs(Graph *g, Path *p, uint32_t v, Path *best_path) {
    graph_visit_vertex(g, v);
    path_add(p, v, g);
    for (uint32_t adj = 0; adj < graph_vertices(g); ++adj) {
        if (graph_get_weight(g, v, adj) && !graph_visited(g, adj)) {
            dfs(g, p, adj, best_path);
        }
    }

    if (graph_get_weight(g, v, START_VERTEX) && path_vertices(p) == graph_vertices(g)) {
        path_add(p, START_VERTEX, g);
        if (path_distance(p) < path_distance(best_path) || !path_distance(best_path)) {
            path_copy(best_path, p);
        }
        path_remove(p, g);
    }

    path_remove(p, g);
    graph_unvisit_vertex(g, v);
}

void print_help(FILE *f) {
    fprintf(f, "Usage: tsp [options]\n\n-i infile    Specify the input file path containing the "
               "cities and edges\n             of a graph. If not specified, the default input "
               "should be\n             set as stdin.\n\n-o outfile   Specify the output file path "
               "to print to. If not specified,\n             the default output should be set as "
               "stdout.\n\n-d           Specifies the graph to be directed.\n\n-h           Prints "
               "out a help message describing the purpose of the\n             graph and the "
               "command-line options it accepts, exiting the\n             program afterwards.\n");
}
