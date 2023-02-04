// ========================================================================
// File: shell_sort2.cpp
// ========================================================================
#include <vector>
#include <cstdlib>
#include <cmath>
#include "project1.h"



// ==== shell_sort2 =======================================================
//
// ========================================================================
void shell_sort2(std::vector<int>& nums)
{
  double k = (int)log2(nums.size());
  
  for(int gap = nums.size() - 1; gap > 0; gap = pow(2, k--) - 1)
    {
      for(int i = gap; i < nums.size(); i++)
	{
	  int temp = nums[i];
	  int j = i;
	  while(j >= gap && temp < nums[j - gap])
	    {
	      nums[j] = nums[j - gap];
	      j-= gap;
	    }
	  nums[j] = temp;
	}
    }

} // end of "shell_sort2"
