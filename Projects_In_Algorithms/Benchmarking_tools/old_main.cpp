// ========================================================================
// File: old_main.cpp
// ========================================================================
#include <vector>
#include <cstdlib>
#include <cmath>
#include "project1.h"
#include <time.h>
#include <iostream>
#include <chrono>
#include <random>

#define SIZE 10

//void uniform_populate(std::vector<int> &in_vector, int in_size);
void populate_vector(std::vector<int> &in_vector, int in_size,
                                                  std::mt19937 &gen);
void display_vector(std::vector<int> &in_vector);
void almost_sort(std::vector<int> &in_vector, int in_size,
		                              std::mt19937 &gen);
std::vector<int> reverse_m_sort(const std::vector<int>& nums);
std::vector<int> reverse_merge(std::vector<int> inV1, std::vector<int> inV2);



// ==== main ==============================================================
//
// ========================================================================
int main()
{
/*
  // ** OLD SEED TEST CODE **
  //  srand(time(NULL));

  typedef std::chrono::high_resolution_clock myclock;
  myclock::time_point beginning = myclock::now();


  // ** SEED GENERATOR 1 **
  // obtain seed froma  user string
  //  std::string str;
  //  std::cout << "Please, enter a seed: ";
  //  std::getline(std::cin, str);
  //  std::seed_seq seed1 (str.begin(), str.end());


  // ** SEED GENERATOR 2 **
  // obtain seed from the timer
  myclock::duration d = myclock::now() - beginning;
  unsigned seed2 = d.count();

  std::mt19937 generator(seed2);
  std::cout << "Seed produced: " << generator() << std::endl;
*/

  // ** WORKING SEED GENERATOR **
  std::vector<int> uniform_vector;
  std::vector<int> almost_sorted_vector;
  std::vector<int> reverse_sorted_vector;

  // Should test results from both clock generators
  //  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();  
  std::mt19937 generator(seed);

  // uniform testing
  populate_vector(uniform_vector, SIZE, generator);
  display_vector(uniform_vector);

  // almost sorted testing
  populate_vector(almost_sorted_vector, SIZE, generator);
  std::cout << "Merge Sort" << std::endl;  
  merge_sort(almost_sorted_vector);
  almost_sort(almost_sorted_vector, SIZE, generator);
  display_vector(almost_sorted_vector);

  // reverse sorted testing
  populate_vector(reverse_sorted_vector, SIZE, generator);
  reverse_sorted_vector = reverse_m_sort(reverse_sorted_vector);
  std::cout << " ** reverse_sorted_vector **" << std::endl;
  display_vector(reverse_sorted_vector);
  
  return 0;
  
} // end of "main"



// ==== populate_vector ===================================================
//
// ========================================================================
void populate_vector(std::vector<int> &in_vector, int in_size,
		                                  std::mt19937 &gen)
{
  std::cout << "** populate_vector **" << std::endl;
  
  for(int i = 0; i < in_size; i++)
    {
      in_vector.push_back(gen() % in_size);
    }
} // end of "populate_vector"



// ==== display_vector ====================================================
//
// ========================================================================
void display_vector(std::vector<int> &in_vector)
{
  std::cout << "** display_vector **" << std::endl;
  
  std::vector<int>::iterator it = in_vector.begin();

  for(int index = 0;it != in_vector.end(); it++, index++)
    {
      std::cout << "Index " << index << ": " << *it << std::endl;
    }
} // display vector



// ==== almost_sort =======================================================
//
// ========================================================================
void almost_sort(std::vector<int> &in_vector, int in_size,
		                              std::mt19937 &gen)
{
  std::cout << " ** almost_sort **" << std::endl;
  int total_pairs = 2*log(in_size);
  std::cout << "Total Pairs: " << total_pairs << std::endl;

  int rand_i;
  int rand_j;
  int temp;

  for(int i = 0; i < total_pairs; i++)
    {
      rand_i = gen() % in_size;
      rand_j = gen() % in_size;

      std::cout << "Swapping Indexes " << rand_i << " and " << rand_j << std::endl;

      temp = in_vector[rand_i];

      in_vector[rand_i] = in_vector[rand_j];
      in_vector[rand_j] = temp;
    }
} // end of "almost sort"



// ==== reverse_m_sort ====================================================
//
// ========================================================================
std::vector<int> reverse_m_sort(const std::vector<int>& nums)
{
    if(nums.size() <=  1)
      return nums;
    else
    {
      int half_size = (int)nums.size()/2;
      std::vector<int> lVec(nums.begin(), nums.begin() + half_size);
      std::vector<int> rVec(nums.begin() + half_size, nums.end());
      
      return reverse_merge(reverse_m_sort(lVec), reverse_m_sort(rVec));
     }
} // end of "reverse_m_sort"



// ==== reverse_merge =====================================================
//
// ========================================================================
std::vector<int> reverse_merge(std::vector<int> inV1, std::vector<int> inV2)
{
  int i = 0, j = 0;

  std::vector<int> out;
  
  while(i < inV1.size() && j < inV2.size())
    {
      if(inV1[i] > inV2[j])
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
} // end of "reverse_merge"
