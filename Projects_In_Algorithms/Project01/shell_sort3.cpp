// ========================================================================
// File: shell_sort3.cpp
// ========================================================================
#include <vector>
#include <cstdlib>
#include <cmath>
#include "project1.h"

std::vector<int> make_pratt_list(const int in_size);


  
// ==== shell_sort3 =======================================================
//
// ========================================================================
void shell_sort3(std::vector<int>& nums)
{
  std::vector<int> pratt_list = make_pratt_list(nums.size());
    
  int i = 0;
  for(int gap = pratt_list[i]; i < pratt_list.size(); gap = pratt_list[++i])
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
} // end of "shell_sort3"



// ==== make_pratt_list ===================================================
//
// ========================================================================
std::vector<int> make_pratt_list(const int in_size)
{
  std::vector<int> pratt;
  int p,q;
  
  for(p = q = 1; q <= in_size; q *= 3)
    {
      p = q;
      
        for(;p <= in_size; p *= 2)
	{

	  int j = 0;

	  if(pratt.size() == 0)
	    pratt.push_back(p);

	  else
	    {
	      // find the location and insert the pratt value into the list
	      // this handles the sorting of the pratt list
	      for(; p < pratt[j]; j++);
	      pratt.insert(pratt.begin() + j, p);
	    }
	}
    }

  return pratt;
} // end of "make_pratt_list"
