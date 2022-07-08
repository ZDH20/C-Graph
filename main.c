#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  Graph_t *g = graph_t_alloc();

  graph_t_add_vertex(g, 'a');
  graph_t_add_vertex(g, 'b');
  graph_t_add_vertex(g, 'c');

  graph_t_add_edge(g, 'a', 'b', 1);
  graph_t_add_edge(g, 'a', 'c', 2);
  graph_t_add_edge(g, 'c', 'd', 3);
  graph_t_add_edge(g, 'd', 'd', 4);

  graph_t_dump(g);

  printf("Vertex count: %lu\n", graph_t_vertex_sz(g));
  printf("Edge count: %lu\n", graph_t_edge_sz(g));

  graph_t_free(g);

  return 0;
}
