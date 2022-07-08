#ifndef GRAPH_H_
#define GRAPH_H_
#include <stdbool.h>
#include <stdlib.h>
#define TODO printf("TODO: on line: [%d]\n", __LINE__);
#define NOOP(x) (void)x;

typedef struct Edge_t Edge_t;
typedef struct Vertex_t Vertex_t;
typedef struct Graph_t Graph_t;

Edge_t *edge_t_alloc(const char data, const int cost);
Vertex_t *vertex_t_alloc(const char data);
Graph_t *graph_t_alloc();
size_t graph_t_vertex_sz(Graph_t*);
size_t graph_t_edge_sz(Graph_t*);
bool graph_t_contains_vertex(Graph_t*, const char);
void graph_t_add_vertex(Graph_t*, const char);
void graph_t_add_edge(Graph_t*, const char, const char, const int);
void graph_t_dump(Graph_t*);
void graph_t_free(Graph_t*);

#endif // GRAPH_H_
