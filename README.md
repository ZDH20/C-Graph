# C-Graph
A simple graph. Vertex data takes type char. Edge data takes type char, cost takes int.

User functions:
  
  edge_t_alloc() -> allocates an edge.
  
  vertex_t_alloc() -> allocates a vertex.
 
  graph_t_alloc() -> allocates a graph.
  
  graph_t_vertex_sz() -> returns the number of verticies.
  
  graph_t_edge_sz() -> returns the number of edges.
  
  graph_t_contains_vertex() -> returns true if a vertex of type char is present in the graph.
  
  graph_t_add_vertex() -> adds a vertex to a graph.
  
  graph_t_add_edge() -> adds an edge to a graph.
  
  graph_t_dump() -> prints all verticies and edges in a graph.
  
  graph_t_free() -> free()'s all memory.
  
Other functions:
  
  validate() -> Makes sure a graph is valid.
  
  panic() -> prints an error message and exits with EXIT_FAILURE.
