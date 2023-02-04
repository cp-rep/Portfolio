#ifndef PROJECT3_H
#define PROJECT3_H

// DO NOT MODIFY THIS FILE 
#include <vector>
#include <map>
#include "graph.h"
#include <fstream>

/******* EXPLANATIONS ********/

// construct a graph using num_nodes nodes and edges (ui, vi) for all i
// implement this function in graph.cpp. you can find an empty definition there
// u and v will be the same length
// (ui, vi) are pairs of integers which can be mapped uniquely to (ui', vi'), pairs of Nodes
// ui, vi values are numbered from 1 to num_nodes, inclusive
Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v, int d);

// network algorithms
// implement these in graph_algorithms.cpp
int get_diameter(Graph graph); 
float get_clustering_coefficient(Graph graph);
std::map<int, int> get_degree_distribution(Graph graph, char* in_arg);
#endif
