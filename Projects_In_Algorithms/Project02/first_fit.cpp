#include "project2.h"
#include <vector>
#include "WAVLTree.h"
#include <algorithm>



// ==== first_fit =========================================================
//
// ========================================================================
void first_fit(const std::vector<double>& items, std::vector<int>& assignment,
	                                      std::vector<double>& free_space)
{
  WAVLTree<int, double> new_tree;

  for(int i = 0; i < items.size(); i++)
      assignment[i] = new_tree.insertFirst(items[i]);
  
  new_tree.updateF(free_space);
} // end of "first_fit"



// ==== first_fit_decreasing ==============================================
//
// ========================================================================
void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment,
			                                 std::vector<double>& free_space)
{

  WAVLTree<int, double> new_tree;  
  std::vector<double>reverse_sorted = items;
  std::sort(reverse_sorted.rbegin(), reverse_sorted.rend());
  
  for(int i = 0; i < reverse_sorted.size(); i++)
      assignment[i] = new_tree.insertFirst(reverse_sorted[i]);
  
  new_tree.updateF(free_space);
} // end of "first_fit_decreasing"
