#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Edge_t {
  char    data;
  int     cost;
  Edge_t *next;
};

struct Vertex_t {
  char      data;
  Edge_t   *edges;
  Vertex_t *next;
};

struct Graph_t {
  Vertex_t *head;
  size_t    vert_sz;
  size_t    edge_sz;
};

void panic(char *err_msg) {
  fprintf(stderr, "ERROR: %s\n", err_msg);
  exit(EXIT_FAILURE);
}

void validate(Graph_t *self) {
  if (!self) {
    panic("graph param is NULL.");
  }
}

Edge_t *edge_t_alloc(const char data, const int cost) {
  Edge_t *new_edge;
  if (!(new_edge = (Edge_t*)malloc(sizeof(Edge_t)))) {
    panic("edge_t_alloc failed to alloc.");
  }
  new_edge->cost = cost;
  new_edge->data = data;
  new_edge->next = NULL;
  return new_edge;
}

Vertex_t *vertex_t_alloc(const char data) {
  Vertex_t *new_vertex;
  if (!(new_vertex = (Vertex_t*)malloc(sizeof(Vertex_t)))) {
    panic("vertex_t_alloc failed to alloc.");
  }
  new_vertex->data  = data;
  new_vertex->edges = NULL;
  new_vertex->next  = NULL;
  return new_vertex;
}

Graph_t *graph_t_alloc() {
  Graph_t *new_graph;
  if (!(new_graph = (Graph_t*)malloc(sizeof(Vertex_t)))) {
    panic("graph_t_alloc failed to alloc.");
  }
  new_graph->edge_sz = 0;
  new_graph->vert_sz = 0;
  new_graph->head    = NULL;
  return new_graph;
}

size_t graph_t_vertex_sz(Graph_t *self) {
  validate(self);
  return self->vert_sz;
}

size_t graph_t_edge_sz(Graph_t *self) {
  validate(self);
  return self->edge_sz;
}

bool graph_t_contains_vertex(Graph_t *self, const char data) {
  validate(self);
  Vertex_t *tmp = self->head;
  while (tmp) {
    if (tmp->data == data) {
      return true;
    }
    tmp = tmp->next;
  }
  return false;
}

void graph_t_add_vertex(Graph_t *self, const char src) {
  // No need to validate self. graph_t_contains_vertex() already does.
  if (graph_t_contains_vertex(self, src)) {
    return;
  }

  Vertex_t *new_vert = vertex_t_alloc(src);
  // Graph is empty. Alternatively use self->vert_sz.
  if (!self->head) {
    self->head = new_vert;
  }
  // Graph is not empty.
  // Append the new_vert to the end of the vertex list.
  else {
    Vertex_t *tmp = self->head;
    self->head = new_vert;
    self->head->next = tmp;
  }
  self->vert_sz++;
}

void graph_t_add_edge(Graph_t *self, const char src, const char dest,
                      const int cost) {
  validate(self);

  bool found_dest    = false;
  Vertex_t *save_pos = NULL;
  Vertex_t *tmp_vert = self->head;
  Edge_t   *new_edge = edge_t_alloc(dest, cost);

  // Travel through verticies currently in graph.
  while (tmp_vert) {
    // Graph already contains src.
    if (tmp_vert->data == src) {
      save_pos = tmp_vert;
    }
    // Graph already contains dest.
    if (tmp_vert->data == dest) {
      found_dest = true;
    }
    tmp_vert = tmp_vert->next;
  }

  // Src was not found in graph. Add it.
  if (!save_pos) {
    graph_t_add_vertex(self, src);
    save_pos = self->head;
  }

  // Dest was not found in graph. Add it.
  if (!found_dest) {
    graph_t_add_vertex(self, dest);
  }

  // Vertex has no edges connected.
  if (!save_pos->edges) {
    save_pos->edges = new_edge;
  }
  // Vertex has edges already. Travel to the end.
  else {
    Edge_t *tmp_edge = save_pos->edges;
    while (tmp_edge->next) {
      tmp_edge = tmp_edge->next;
    }
    tmp_edge->next = new_edge;
  }
  self->edge_sz++;
}

void graph_t_dump(Graph_t *self) {
  validate(self);
  Vertex_t *tmp_vert = self->head;
  Edge_t *tmp_edge   = NULL;
  // Print verticies.
  while (tmp_vert) {
    printf("Vertex: %c", tmp_vert->data);
    tmp_edge = tmp_vert->edges;
    // Print edges.
    while (tmp_edge) {
      printf(" -> [%c, %d]", tmp_edge->data, tmp_edge->cost);
      tmp_edge = tmp_edge->next;
    }
    tmp_vert = tmp_vert->next;
    putchar('\n');
  }
}

void graph_t_free(Graph_t *self) {
  validate(self);

  Vertex_t *del_vert = NULL;
  Edge_t *del_edge   = NULL;

  // Free verticies.
  while (self->head) {
    del_vert = self->head;
    // Free edges.
    while (self->head->edges) {
      del_edge = self->head->edges;
      self->head->edges = self->head->edges->next;
      free(del_edge);
    }
    // Free vertex.
    self->head = self->head->next;
    free(del_vert);
  }
  free(self);
}
