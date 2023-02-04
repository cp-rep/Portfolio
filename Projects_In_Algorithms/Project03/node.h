#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>

class Node {
 public:
  // DO NOT MODIFY MEMBERS BELOW THIS LINE
  // used for comparing two nodes, already implemented	
  bool operator==(const Node& other) const {return id == other.id;}

  // uniquely identifies a node (no two nodes have the same id).   
  int id;
  
  // id must be set in the constructor and thereafter not modified
  Node(){}

  // don't use this constructor, implement another one that accepts node id as an argument 
  // DO NOT MODIFY MEMBERS ABOVE THIS LINE
  
  // you should declare a constructor/any other members you need
  // implement any newly declared member functions in node.cpp

  // constructor
  Node(int in_id);
  
  // member functions
  int get_degree();  

  // member variables
  std::vector<int> neighbors;
};

#endif
