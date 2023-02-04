// ========================================================================
// File: hybrid_sort2.cpp
// ========================================================================
#include <vector>
#include <cmath>
#include "project1.h"

std::vector<int> merge2(std::vector<int> inV1, std::vector<int> inV2);
std::vector<int> h_sort2(std::vector<int>& nums, int h);



// ==== hybrid_sort2 ======================================================
//
// ========================================================================
void hybrid_sort2(std::vector<int>& nums)
{
  nums = h_sort2(nums, nums.size());
} // end of "hybrid_sort2"



// ==== h_sort2 ===========================================================
//
// ========================================================================
std::vector<int> h_sort2(std::vector<int>& nums, int h)
{
  h = (int)cbrt(nums.size());
  
  if(nums.size() > h)
    {
      int half_size = (int)nums.size()/2;
      std::vector<int> lVec(nums.begin(), nums.begin() + half_size);
      std::vector<int> rVec(nums.begin() + half_size, nums.end());

      return merge2(h_sort2(lVec,h), h_sort2(rVec, h));
    }
  else
    {
      insertion_sort(nums);
      return nums;
    }
} // end of "h_sort2"



// ==== merge2 ============================================================
//
// ========================================================================
std::vector<int> merge2(std::vector<int> inV1, std::vector<int> inV2)
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
} // end of "merge2"
