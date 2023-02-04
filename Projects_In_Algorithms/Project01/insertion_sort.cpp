// ========================================================================
// File: insertion_sort.cpp
// ========================================================================
#include <vector>
#include "project1.h"



// ==== insertion_sort ====================================================
//
// ========================================================================
void insertion_sort(std::vector<int>& nums)
{
  for(int i = 1; i < nums.size(); i++)
    {
      int temp = nums[i];

      int j = i;
      while(j > 0 && nums[j - 1] > temp)
	{
	  nums[j] = nums[j - 1];
	  j--;
	}

      nums[j] = temp;
    }
} // end of "insertion_sort"
