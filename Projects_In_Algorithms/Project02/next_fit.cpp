#include "WAVLTree.h"
#include "project2.h"
#include <vector>


// ==== next_fit ==========================================================
//
// ========================================================================
void next_fit(const std::vector<double>& items, std::vector<int>& assignment,
	                                     std::vector<double>& free_space)
{
  for(int i = 0; i < items.size(); i++)
    {
      if(free_space.empty())
	{
	  free_space.push_back(1);	  
	}
      
      if(free_space.back() < items[i])
	free_space.push_back(1 - items[i]);	  	
      else
	free_space.back() = free_space.back() - items[i];		  
      assignment[i] = free_space.size();
    }
} // end of "next_fit"
