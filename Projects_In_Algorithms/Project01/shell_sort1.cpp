// ========================================================================
// File: shell_sort1.cpp
// ========================================================================
#include <vector>
#include <cstdlib>
#include "project1.h"



// ==== shell_sort1 =======================================================
//
// ========================================================================
void shell_sort1(std::vector<int>& nums)
{
  for(int gap = (nums.size() / 2); gap > 0; gap /= 2)
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
  
} // end of "shell_sort1"
