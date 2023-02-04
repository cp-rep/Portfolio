#include "graph.h"
#include "node.h"

unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 generator(seed);



// ==== Graph Constructor ==================================================
//
// =========================================================================
Graph::Graph()
{
  m_num_nodes = 0;
  m_num_edges = 0;
  m_num_triangles = 0;
} // end of "Graph Constructor"



// ==== make_graph =========================================================
//
// =========================================================================
Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v){
  Graph *graph = new Graph;
   
  graph->m_num_nodes = num_nodes;
  graph->m_adjacency_list = new std::unordered_set<int>[num_nodes+1];

  // insert the 0 node
  graph->m_adjacency_list[0].insert(0);

  // add all the nodes
  for(int i = 0; i < num_nodes; i++)
    {
      Node *node = new Node(i+1);
      graph->m_vertice.push_back(*node); 
    }

  // add the edges
  for(int i = 0; i < u.size(); i++)
    {
      if(u[i] != 0 && v[i] != 0)
      	{
	  graph->add_edge(graph, u[i], v[i]);
	  graph->m_num_edges++;
	}
    }

  return *graph;
} // end of "make_graph"



// ==== get_num_nodes ======================================================
//
// =========================================================================
int Graph::get_num_nodes() {
  return m_num_nodes;
} // end of "get_num_nodes"



// ==== get_num_edges ======================================================
//
// =========================================================================
int Graph::get_num_edges() {
  return m_num_edges;
} // end of "get_num_edges"



// ==== get_neighbors ======================================================
//
// =========================================================================
std::vector<Node> Graph::get_neighbors(Node u) {
  std::vector<Node> naybes;
  int neighbor = 0;
  
  for(int i = 0; i < u.neighbors.size(); i++)
    {
      neighbor = u.neighbors[i];
      naybes.push_back(m_vertice[neighbor - 1]);
    }

  return naybes;
} // end of "get_neighbors"



// ==== get_id_to_node_map =================================================
//
// =========================================================================
std::map<int, Node> Graph::get_id_to_node_map(){
  std::map<int, Node> id_node_map;
  
  id_node_map.insert(std::pair<int, Node>(0,0));

  for(int i = 0; i < m_num_nodes; i++)
      id_node_map.insert(std::pair<int, Node>(m_vertice[i].id, m_vertice[i]));

  return id_node_map;
} // end of "get_id_to_node_map"



// ==== add_edge ===========================================================
//
// =========================================================================
void Graph::add_edge(Graph *graph, int u, int v)
{
  graph->m_vertice[u-1].neighbors.push_back(v);
  graph->m_adjacency_list[u].insert(v);
  graph->m_vertice[v-1].neighbors.push_back(u);
  graph->m_adjacency_list[v].insert(u);
} // end of "add_edge"



// ==== get_random_vertice =================================================
//
// =========================================================================
int Graph::get_random_vertice()
{
  int r;
  
  while(true)
    {
      r = generator() % (m_num_nodes + 1);
      if(r != 0)
	break;
    }

    return r;
} // end of "get_random_vertice"



// ==== graph_BFS ==========================================================
//
// =========================================================================
int Graph::graph_BFS(int r)
{
  std::list<int> vertices;  
  bool *visit = new bool[m_num_nodes];
  std::unordered_set<int>::iterator it;  
  
  for(int i = 0; i < m_num_nodes; i++)
    visit[i] = false;

  visit[r] = true;
  vertices.push_back(r);

  while(!vertices.empty())
    {
      r = vertices.front();
      vertices.pop_front();

      for(it = m_adjacency_list[r].begin(); it != m_adjacency_list->end(); it++)
	{
	  if(!visit[*it])
	    {
	      visit[*it] = true;
	      vertices.push_back(*it);
	    }
	}
    }

  return r;
} // end of "graph_BFS"



// ==== shortest_graph_BFS ==========================================================
//
// =========================================================================
bool Graph::shortest_graph_BFS(int parents[], int distance[], int r, int w)
{
  std::list<int> vertices;
  std::unordered_set<int>::iterator it;  
  bool visit[m_num_nodes];

  for(int i = 0; i < m_num_nodes; i++)
    {
      parents[i] = -1;
      distance[i] = INT_MAX;            
      visit[i] = false;
    }

  vertices.push_back(r);  
  distance[r] = 0;  
  visit[r] = true;

  while(!vertices.empty())
    {
      r = vertices.front();      
      vertices.pop_front();
      
      for(it = m_adjacency_list[r].begin(); it != m_adjacency_list->end(); it++)	
	{
	  if(!visit[*it])
	    {
	      visit[*it] = true;
	      distance[*it] = distance[r] + 1;
	      parents[*it] = r;
	      vertices.push_back(*it);

	      if(*it == w)
		{
		  parents[r] = -1;
		  return true;
		}
	    }
	}
    }

  return false;
} // end of "shortest_graph_BFS"



// ==== get_shortest_distance ==============================================
//
// =========================================================================
int Graph::get_shortest_distance(int r, int w)
{
  std::vector<int> shortest_path;
  int current;
  int shortest_distance ;  
  int parents[m_num_nodes];
  int distance[m_num_nodes];

  for(int i = 0; i < m_num_nodes; i++)
    {
      parents[i] = -1;      
      distance[i] = INT_MAX;
    }

  shortest_distance = shortest_graph_BFS(parents, distance, r, w);
  
  if(!shortest_distance)
    return -1;
  else{
    current = w;
  
    while(parents[current] != -1)
      {
	shortest_path.push_back(parents[current]);
	current = parents[current];
      }
  }
  
  return distance[w];
} // end of "get_shortest_distance"



// ==== graph_degeneracy ===================================================
//
// =========================================================================
int Graph::graph_degeneracy(Graph graph)
{
  // 2 & 3
  graph.make_D();

  // 4
  graph.N.resize(m_num_nodes);

  // 5 
  graph.K = 0;
  
  // 6
  // while(true)
  for(int n = 0; n < graph.m_num_nodes; n++)
    {
      // get smallest i non empty D[i]
      int i;
      for(i = 0; graph.D[i].size() == 0; i++);

      // set k max (k, i) 
      graph.K = std::max(K, i);

      // select vertex v from D[i]
      int v;
      v = graph.D[i].back();

      // add v to beginning of L
      graph.L.push_front(v);

      // remove v from D[i]
      graph.D[i].pop_back();

      // mark v as being in L
      graph.H[v] = true;

      // testing all neighbors of v
      for(int q = 0; q < graph.m_vertice[v-1].neighbors.size(); q++)
	{
	  int w = graph.m_vertice[v-1].neighbors[q];	

	  // for each neighbor w of v that is not already already in L
	  if(!graph.H[w])
	    {
	      // get Degree[w]
	      int dw = graph.all_D[w - 1]; // account zero based 

	      // subtract 1 from Degree[w]
	      if(graph.all_D[w - 1] > 0)
		graph.all_D[w - 1] -= 1;

	      // Update DW
	      dw = graph.all_D[w - 1];
	      
	      // move w to the cell of D corresponding to the new value dw
	      graph.D[dw].push_back(graph.m_vertice[v-1].neighbors[q]);

	      // find original location of w in D to erase it since we moved it
	      for(int zk = 0; zk < graph.D[dw + 1].size(); zk++)
		  if(graph.D[dw +1][zk] == w)
		      graph.D[dw + 1].erase(graph.D[dw +1].begin() + zk);

	      // add w to Nv
	      graph.N[v - 1].push_back(w);	      
	    }
	}
    }

  return graph.count_triangles();
} // end of "graph_degeneracy"



// ==== count_triangles ===================================================
//
// ========================================================================
int Graph::count_triangles()
{
  int u;
  int w;
  int t = 0;
  for(int i = 0; i < L.size(); i++)
    {
      for(int j = 0; j < m_vertice[L.front() - 1].neighbors.size() - 1; j++)
	{
	  if(m_vertice[L.front() - 1].neighbors[j])
	      u = m_vertice[L.front() - 1].neighbors[j];
	  
	  for(int k = j + 1; k < (m_vertice[L.front() - 1].neighbors.size()); k++)
	    {
	      if(m_vertice[L.front() - 1].neighbors[k])
		{
		  w = m_vertice[L.front() - 1].neighbors[k];
		  if(is_in_N(L.front() - 1, u, w))
		    if(is_edge(u, w))
		      m_num_triangles++;
		}
	    }
	}
      
      int temp = L.front();
      L.pop_front();
      L.push_back(temp);
    }

  return m_num_triangles;
} // end of "count_triangles"



// ==== is_in_N ===========================================================
//
// ========================================================================
bool Graph::is_in_N(int v, int u, int w)
{
  bool u_flag = false;
  bool w_flag = false;

  for(int i = 0; i < N[v].size(); i++)
    {
      if(N[v][i] == u)
	u_flag = true;
      if(N[v][i] == w)
	w_flag = true;
    }

  if(u_flag && w_flag)
    return true;
  else
    return false;
} // end of "is_in_N"



// ==== make_D ============================================================
//
// ========================================================================
void Graph::make_D()
{
  D.resize(m_num_nodes + 1);
  
  for(int i = 1; i < m_num_nodes + 1; i++)
    {
      // get degrees of every node, store by index of vertice
      all_D.push_back(m_vertice[i-1].get_degree());

      // D[i] = list of vertices not already in L for dv = i
      D[all_D[i - 1]].push_back(i);
    }
} // end of "make_D"



// ==== print_D ============================================================
//
// =========================================================================
void Graph::print_D()
{
  for(int i = 0; i < D.size(); i ++)
    {
      std::cout << "D: " << i << ":";
      for(int j = 0; j < D[i].size(); j++)
	  std::cout << " " << D[i][j];
      std::cout << std::endl;;
    }
} // end of "print_D"



// ==== print_degrees ======================================================
//
// =========================================================================
void Graph::print_degrees(std::vector<int> in_vector)
{
  for(int i = 0; i < in_vector.size(); i++)
      std::cout << "Degree " << i + 1 << ": " << in_vector[i] << std::endl;
} // end of "print_degrees"



// ==== print_neighbors ====================================================
//
// =========================================================================
void Graph::print_neighbors()
{
  std::cout << std::endl;
  for(int i = 0; i < m_vertice.size(); i++)
    {
      std::cout << "Neighbors of " << i + 1 << ": ";
      for(int j = 0; j < m_vertice[i].neighbors.size(); j++)
	std::cout << m_vertice[i].neighbors[j] << " ";
      std::cout << std::endl;
    }
} // end of "print_neighbors"



// ==== print_L ============================================================
//
// =========================================================================
void Graph::print_L()
{
  std::list<int>::iterator it;
  int i = 0;
  for(it = L.begin(); it != L.end(); it++, i++)
      std::cout << "L " << i + 1 << ": " << *it << std::endl;
} // end of "print_L"



// ==== print_N ============================================================
//
// =========================================================================
void Graph::print_N()
{
  for(int i = 0; i < N.size(); i ++)
    {
      std::cout << "N " << i + 1 << ":";
      for(int j = 0; j < N[i].size(); j++)
	{
	  std::cout << " " << N[i][j];
	}
      std::cout << std::endl;;
    }
} // end of "print_N"



// ==== is_edge ============================================================
//
// =========================================================================
bool Graph::is_edge(int u, int w)
{
  for(int i = 0; i < m_vertice[u-1].neighbors.size(); i++)
    if(m_vertice[u-1].neighbors[i] == w)
      return true;

  return false;
} // end of "is_edge"



// ==== compute_degree =====================================================
//
// =========================================================================
void Graph::compute_degrees()
{
  // clear degrees since we used this data structure before
  for(int i = 1; i < m_num_nodes + 1; i++)
      // get degrees of every node, store by index of vertice
      all_degrees.push_back(m_vertice[i-1].get_degree());
} // end of "compute_degree"



// ==== initialize_histogram ===============================================
//
// =========================================================================
void Graph::initialize_histogram()
{
  for(int i = 0; i < all_degrees.size(); i++)
      hist.insert(std::pair<int, int>(i, 0));
} // end of "initialize_histogram"



// ==== print_degree_distribution ==========================================
//
// =========================================================================
void Graph::print_degree_distribution()
{
  std::map<int, int>::iterator it;
  int i = 0;
  
  for(it = hist.begin(); it != hist.end(); it++, i++)
      std::cout << "Hist " << it->first << ": " << it->second << std::endl;
} // end of "print_degree_distribution"
