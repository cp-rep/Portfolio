#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <vector>
#include "node.h"
#include <bits/stdc++.h>
#include <algorithm>
#include <chrono>
#include <time.h>
#include <utility>
#include <iostream>



class Graph 
{
 public:
  // DO NOT MODIFY MEMBERS BELOW THIS LINE
  int get_num_nodes(); // get number of nodes
  int get_num_edges(); // get number of edges
  std::vector<Node> get_neighbors(Node u);  // return neighbors of u 
  std::map<int, Node> get_id_to_node_map(); // allows lookup of nodes from ids
  // DO NOT MODIFY MEMBERS ABOVE THIS LINE
		
  // declare any constructors, members, and member functions you may want to use
  // implement any newly declared member functions in graph.cpp

  // constructor
  Graph();

  // member functions
  void add_edge(Graph *graph, int u, int v);
  int graph_BFS(int r);
  bool shortest_graph_BFS(int parents[], int distance[], int r, int w);
  int get_shortest_distance(int r, int w);
  int graph_degeneracy(Graph graph);
  void initialize_histogram();
  int get_random_vertice();
  int count_triangles();
  void compute_degrees();  
  bool is_in_N(int v, int u, int w);
  bool is_edge(int u, int w);
  void make_D();
  void make_N();

  // printing members
  void print_neighbors();
  void print_degrees(std::vector<int> in_vector);
  void print_degree_distribution();
  void print_L();
  void print_D();
  void print_N();

  // members
  int m_num_nodes;
  int m_num_edges;
  int m_num_triangles;
  std::vector<Node> m_vertice;
  std::unordered_set<int>* m_adjacency_list;

  // degeneracy members
  std::vector<std::vector<int>> D;
  std::vector<std::vector<int>> N;  
  std::list<int> L;
  std::vector<int> all_D;
  std::unordered_map<int, bool> H;
  int K;

  // degree distribution members
  std::vector<int> all_degrees;
  std::map<int, int> hist;
};

#endif
