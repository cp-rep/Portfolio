// ========================================================================
// File: shell_sort4.cpp
// ========================================================================
#include <vector>
#include <cstdlib>
#include <cmath>
#include "project1.h"

std::vector<int> generate_sequence(const std::vector<int> &in_nums);



// ==== shell_sort4 =======================================================
//
// ========================================================================
void shell_sort4(std::vector<int>& nums)
{
  std::vector<int> sequence;
  
  sequence = generate_sequence(nums);
  
  int j = 0;
  
  j = sequence.size();
  for(;sequence[j] < nums.size(); j++);
  j--;

  for(int gap = sequence[j]; gap > 0; gap = sequence[--j])
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
} // end of "shell_sort4"



// ==== generate_sequence =================================================
//
// ========================================================================
std::vector<int> generate_sequence(const std::vector<int> &in_nums)
{
  int temp = 0;
  std::vector<int> sequence;
  sequence.push_back(1);

  for(int i = 0; temp < in_nums.size() - 1; i++)
    {
      temp = (pow(4, i + 1) + (3 * (pow(2, i))) + 1);
      sequence.push_back(temp);
    }

  sequence.pop_back();
  
  return sequence;
} // end of "generate_sequence"
