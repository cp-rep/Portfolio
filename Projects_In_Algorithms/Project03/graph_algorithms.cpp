#include "graph.h"



// ==== get_diameter =======================================================
//
// =========================================================================
int get_diameter(Graph graph)
{
  int r = 0;
  int w = 0;
  int distance = 0;
  int d_max;

  // get random vertice
  r = graph.get_random_vertice();

  // set Dmax 0
  d_max = 0;

  while(true)
    {
      w = graph.graph_BFS(r);
      distance = graph.get_shortest_distance(r, w);
	  
      if(distance > d_max)
	{
	  d_max = distance;
	  r = w;
	}
      else
	break;
    }

  return d_max;
} // end of "get_diameter"



// ==== get_clustering_coefficient==========================================
//
// =========================================================================
float get_clustering_coefficient(Graph graph) 
{
  int temp;
  int result;
  int degree = 0;
  int triangles;
  
  triangles = graph.graph_degeneracy(graph);
  triangles = 3 * triangles;
  
  // calculate denominators and push them onto the vector
  for(int i = 0; i < graph.m_num_nodes; i++)
    {
      result = graph.m_vertice[i].get_degree();
      temp = (result - 1);
      result = (result * temp);
      result = (result/2);
      degree += result;
    }
  
  return ((float)triangles/(float)degree);
} // end of "get_clustering_coefficient"



// ==== get_degree_distribution ============================================
//
// =========================================================================
std::map<int, int> get_degree_distribution(Graph graph) 
{
  graph.compute_degrees();
  graph.initialize_histogram();
  
  for(int i = 0; i < graph.hist.size(); i++)
      graph.hist[graph.all_degrees[i]]++;

  std::map<int, int>::iterator it;
  for(it = graph.hist.begin(); it != graph.hist.end(); it++)
      if(it->second == 0)
	graph.hist.erase(it);
  
  return graph.hist;
} // end of "get_degree_distribution"
