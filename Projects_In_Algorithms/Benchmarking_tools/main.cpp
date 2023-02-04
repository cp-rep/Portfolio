// ========================================================================
// File: main.cpp
// ========================================================================
#include <vector>
#include <cstdlib>
#include <cmath>
#include "project1.h"
#include <time.h>
#include <iostream>
#include <chrono>
#include <random>
#include <sstream>
#include <string.h>
#include <map>
#include <fstream>
#include <algorithm>

//#define SIZE 10

// function prototypes
void populate_vector(std::vector<int> &in_vector, int in_size,
                                                  std::mt19937 &gen);
void display_vector(std::vector<int> &in_vector);
void almost_sort(std::vector<int> &in_vector, int in_size,
		                              std::mt19937 &gen);
std::vector<int> reverse_m_sort(const std::vector<int>& nums);
std::vector<int> reverse_merge(std::vector<int> inV1, std::vector<int> inV2);
void populate_uniform_vector(std::vector<int> &in_vector, int in_size);
int my_random(int ran_val);



unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();  
std::mt19937 generator(seed);

// ==== main ==============================================================
//
// ========================================================================
int main(int argc, char ** argv)
{
  // check for proper execution command
  if(argc != 5)
    {
      std::cerr << "Incorrect arguments. Exiting" << std::endl;
      return -1;
    }


  std::fstream fs;

  fs.open(argv[4], std::fstream::in | std::fstream::out | std::fstream::app);

  // create seed
  //  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  //  unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();  
  //  std::mt19937 generator(seed);

  // get the function name to call and save to string
  std::string func_string = argv[1];
  /*  std::cout << "Function: " << func_string << std::endl; */
  
  // get input size from argv and store in an integer
  int size = 0;
  std::string input_size = argv[2];
  std::stringstream conv_str(input_size);
  conv_str >> size;
  /*  std::cout << "Input Size: " << size << std::endl; */


  // create function pointer and map function
  typedef std::vector<int> (*sort_fn) (std::vector<int>& nums);
  /*  typedef void (*sort_fn) (std::vector<int>& nums);  */
  std::map<std::string, sort_fn> name_to_fn;

  // create local vectors for testing
  std::vector<int> uniform_vector01;
  std::vector<int> uniform_vector02;
  
  // get type of list to create
  char list_type = argv[3][0];

  switch(list_type)
    {
    case 'u':
      // vec 1
      populate_uniform_vector(uniform_vector01, size);
      std::random_shuffle(uniform_vector01.begin(), uniform_vector01.end(), my_random);
      // vec 2
      populate_uniform_vector(uniform_vector02, size);
      std::random_shuffle(uniform_vector02.begin(), uniform_vector02.end(), my_random);      
      break;
    case 'a':
      // vec 1
      populate_uniform_vector(uniform_vector01, size);
      std::random_shuffle(uniform_vector01.begin(), uniform_vector01.end(), my_random);
      uniform_vector01 = merge_sort(uniform_vector01);
      almost_sort(uniform_vector01, size, generator);

      // vec 2
      populate_uniform_vector(uniform_vector02, size);
      std::random_shuffle(uniform_vector02.begin(), uniform_vector02.end(), my_random);
      uniform_vector02 = merge_sort(uniform_vector02);
      almost_sort(uniform_vector02, size, generator);
      break;
    case 'r':
      // vec 1
      populate_uniform_vector(uniform_vector01, size);
      std::random_shuffle(uniform_vector01.begin(), uniform_vector01.end(), my_random);
      uniform_vector01 = reverse_m_sort(uniform_vector01);

      // vec 2
      populate_uniform_vector(uniform_vector02, size);
      std::random_shuffle(uniform_vector02.begin(), uniform_vector02.end(), my_random);
      uniform_vector02 = reverse_m_sort(uniform_vector02);      
      break;
    default:
      std::cerr << "Invalid input. Exiting" << std::endl;
      return -1;
      break;
    }
  
  double clock_val = 0;
  auto start = std::chrono::steady_clock::now();  
  // sort the list by sort type
  if(!func_string.compare("insertion_sort"))
    {
      //      std::cout << "insertion_sort" << std::endl;
      sort_fn insertion_sort_fn = insertion_sort;
      insertion_sort_fn(uniform_vector01);
      insertion_sort_fn(uniform_vector02);
      //      display_vector(uniform_vector);      	  
    }
  else if(!func_string.compare("merge_sort"))
    {
      //      std::cout << "merge_sort" << std::endl;
      sort_fn merge_sort_fn = merge_sort;
      uniform_vector01 = merge_sort_fn(uniform_vector01);
      uniform_vector02 = merge_sort_fn(uniform_vector02);      
      //      display_vector(uniform_vector);
    }
  else if(!func_string.compare("shell_sort1"))
    {
      //      std::cout << "shell_sort1" << std::endl;
      sort_fn shell_sort1_fn = shell_sort1;
      uniform_vector01 = shell_sort1_fn(uniform_vector01);
      uniform_vector02 = shell_sort1_fn(uniform_vector02);      
      //      display_vector(uniform_vector);
    }
  else if(!func_string.compare("shell_sort2"))
    {
      //      std::cout << "shell_sort2" << std::endl;
      sort_fn shell_sort2_fn = shell_sort2;
      uniform_vector01 = shell_sort2_fn(uniform_vector01);
      uniform_vector02 = shell_sort2_fn(uniform_vector02);      
      //      display_vector(uniform_vector);
    }
  else if(!func_string.compare("shell_sort3"))
    {
      //      std::cout << "shell_sort3" << std::endl;
      sort_fn shell_sort3_fn = shell_sort3;
      uniform_vector01 = shell_sort3_fn(uniform_vector01);
      uniform_vector02 = shell_sort3_fn(uniform_vector02);      

      //      display_vector(uniform_vector);
    }
  else if(!func_string.compare("shell_sort4"))
    {
      //      std::cout << "shell_sort4" << std::endl;
      sort_fn shell_sort4_fn = shell_sort4;
      uniform_vector01 = shell_sort4_fn(uniform_vector01);
      uniform_vector02 = shell_sort4_fn(uniform_vector02);
      //      display_vector(uniform_vector);
    }
  else if(!func_string.compare("hybrid_sort1"))
    {
      //      std::cout << "hybrid_sort1" << std::endl;
      sort_fn hybrid_sort1_fn = shell_sort4;
      uniform_vector01 = hybrid_sort1_fn(uniform_vector01);
      uniform_vector02 = hybrid_sort1_fn(uniform_vector02);
      //      display_vector(uniform_vector);
    }
  else if(!func_string.compare("hybrid_sort2"))
    {
      //      std::cout << "hybrid_sort2" << std::endl;
      sort_fn hybrid_sort2_fn = shell_sort4;
      uniform_vector01 = hybrid_sort2_fn(uniform_vector01);
      uniform_vector02 = hybrid_sort2_fn(uniform_vector02);
      //      display_vector(uniform_vector);
    }
  else if(!func_string.compare("hybrid_sort3"))
    {
      //      std::cout << "hybrid_sort3" << std::endl;
      sort_fn hybrid_sort3_fn = shell_sort4;
      uniform_vector01 = hybrid_sort3_fn(uniform_vector01);
      uniform_vector02 = hybrid_sort3_fn(uniform_vector02);
      //      display_vector(uniform_vector);
    }
  else
    {
      std::cerr << "Unrecognized input string" << std::endl;
      return -1;
    }
  
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = end-start;
  //  std::cout << "Time to sort: " << diff.count() << std::endl;
  double dividend = 2.00;
  
  // output the formatted data
  fs << input_size;
  fs << ", ";
  fs << (diff.count() / dividend);
  fs << '\n';
  fs.close();
  
  return 0;
} // end of "main"



// ==== populate_vector ===================================================
//
// ========================================================================
void populate_vector(std::vector<int> &in_vector, int in_size,
		                                  std::mt19937 &gen)
{
  /*  std::cout << "** populate_vector **" << std::endl; */
  
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
  /*   std::cout << " ** almost_sort **" << std::endl; */
  int total_pairs = 2*log(in_size);
  /*   std::cout << "Total Pairs: " << total_pairs << std::endl; */

  int rand_i;
  int rand_j;
  int temp;

  for(int i = 0; i < total_pairs; i++)
    {
      rand_i = gen() % in_size;
      rand_j = gen() % in_size;

      /*      std::cout << "Swapping Indexes " << rand_i << " and " << rand_j << std::endl; */

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



// ==== reverse_merge =====================================================
//
// ========================================================================
void populate_uniform_vector(std::vector<int> &in_vector, int in_size)
{
  for(int i = 0; i < in_size; i++)
    {
      in_vector.push_back(i);
    }

  //  display_vector(in_vector);
} // end of "populate_uniform_vector"



//int my_random(std::mt19937 &gen)
int my_random(int ran_val)
{
  return generator() % ran_val;
}
