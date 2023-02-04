#include <vector>
#include "WAVLTree.h"
#include "project2.h"
#include <algorithm>

void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  double temp = 1;
  int best_bin;
  int none_found = 0;
  int prev_best = 0;

  free_space.push_back(1);

  int j;
  for(int i = 0; i < items.size(); i++)
    {
      temp = 1;
      prev_best = 0;
      best_bin = 0;
      none_found = 0;
      j = 0;
      for(j = 0; j < free_space.size(); j++)
	{
	  
	  double current = free_space[j] - items[i];
	  
	  if(current >= 0)
	    { 
	      if(current < temp)
		{
		  prev_best = j;
		  temp = current;
		}
	      	      
	      double best_temp = free_space[best_bin] - items[i];

	      if(best_temp > temp)
		{
		  best_bin = j;
		  if(free_space[prev_best] < free_space[best_bin])
		    best_bin = prev_best;
		}
	    }
	  else
	    {
	      none_found++;
	      if(best_bin == j)
		{
		  best_bin++;
		}
	    }

	}
      if(!none_found)
	{
	  free_space[best_bin] -= items[i];
	  assignment[i] = best_bin + 1;
	}
      
      else if(none_found == j)
	{
	  free_space.push_back(1);
	  free_space[j] -= items[i];
	  assignment[i] = j + 1;
	}
      else
	{
	  free_space[best_bin] -= items[i];
	  assignment[i] = best_bin + 1;
	}
    }
}


void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  std::vector<double>reverse_sorted = items;
  std::sort(reverse_sorted.rbegin(), reverse_sorted.rend());

 double temp = 1;
  int best_bin;
  int none_found = 0;
  int prev_best = 0;

  free_space.push_back(1);

  int j;
  for(int i = 0; i < reverse_sorted.size(); i++)
    {
      temp = 1;
      prev_best = 0;
      best_bin = 0;
      none_found = 0;
      j = 0;
      for(j = 0; j < free_space.size(); j++)
	{
	  
	  double current = free_space[j] - reverse_sorted[i];
	  
	  if(current >= 0)
	    { 
	      if(current < temp)
		{
		  prev_best = j;
		  temp = current;
		}
	      	      
	      double best_temp = free_space[best_bin] - reverse_sorted[i];

	      if(best_temp > temp)
		{
		  best_bin = j;
		  if(free_space[prev_best] < free_space[best_bin])
		    best_bin = prev_best;
		}
	    }
	  else
	    {
	      none_found++;
	      if(best_bin == j)
		{
		  best_bin++;
		}
	    }

	}
      if(!none_found)
	{
	  free_space[best_bin] -= reverse_sorted[i];
	  assignment[i] = best_bin + 1;
	}
      
      else if(none_found == j)
	{
	  free_space.push_back(1);
	  free_space[j] -= reverse_sorted[i];
	  assignment[i] = j + 1;
	}
      else
	{
	  free_space[best_bin] -= reverse_sorted[i];
	  assignment[i] = best_bin + 1;
	}
    } 

}
