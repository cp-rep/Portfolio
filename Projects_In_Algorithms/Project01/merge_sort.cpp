// ========================================================================
// File: merge_sort.cpp
// ========================================================================
#include <vector>
#include "project1.h"

std::vector<int> merge(std::vector<int> inV1, std::vector<int> inV2);
std::vector<int> m_sort(const std::vector<int>& nums);



// ==== merge_sort ========================================================
//
// ========================================================================
void merge_sort(std::vector<int>& nums)
{
    nums = m_sort(nums);
} // end of "merge_sort"



// ==== m_sort ============================================================
//
// ========================================================================
std::vector<int> m_sort(const std::vector<int>& nums)
{
    if(nums.size() <=  1)
      return nums;
    else
    {
      int half_size = (int)nums.size()/2;
      std::vector<int> lVec(nums.begin(), nums.begin() + half_size);
      std::vector<int> rVec(nums.begin() + half_size, nums.end());
      
      return merge(m_sort(lVec), m_sort(rVec));
     }
} // end of "m_sort"



// ==== merge =============================================================
//
// ========================================================================
std::vector<int> merge(std::vector<int> inV1, std::vector<int> inV2)
{
  int i = 0, j = 0;

  std::vector<int> out;
  
  while(i < inV1.size() && j < inV2.size())
    {
      if(inV1[i] < inV2[j])
	{
	  out.push_back(inV1[i++]); 	  
	}
      else
	{
	  out.push_back(inV2[j++]); 	  
 	}
    }

  while(i < inV1.size())
    {
      out.push_back(inV1[i++]);       
    }
  while(j < inV2.size())
    {
      out.push_back(inV2[j++]);             
    }

  return out;
} // end of "merge"
