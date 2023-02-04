#include <iostream>
#include <algorithm> 
#include <stdlib.h>
#include "project1.h"

std::vector<int> generateTest(int sz, int maxVal, int type)
{
	// sz: size of generated sequence,  maxVal: maximum value that the sequence can have
	// type = 1: random sequence
	// type = 2: almost sorted
	// type = 3: sorted in reverse
	std::vector<int> result;
	for (int i = 0; i < sz; i++) {
		result.push_back(rand() % maxVal + 1);
	}
	switch(type) {
		case 1:
			break;
		case 2:
			std::sort(result.begin(), result.end());
			// 10% unsorted
			for (int i = 0; i < sz/10; i++) {
				std::swap(result[rand() % sz], result[rand() % sz]);
			}
			break;
		case 3:
			std::sort(result.rbegin(), result.rend());
			break;
	}
	return result;
}



void testAlgorithm(std::vector<int> test, void (*algorithm)(std::vector<int>&))
{
	std::vector<int> v1 = test, v2 = test;
	std::sort(v1.begin(), v1.end());
	algorithm(v2);
	if (v1 == v2) {
		std::cout << "CORRECT" << std::endl;
	} else {
		std::cout << "INCORRECT" << std::endl;
	}
}



int main()
{
	// generate new tests
	std::vector<std::vector<int> > tests; 
	tests.push_back(generateTest(10, 10, 1));
	tests.push_back(generateTest(100, 100, 2));
	tests.push_back(generateTest(1000, 1000, 3));

	// try algorithms on generated tests
	// remember to add the '&' operator before the function name
	for (auto test: tests) {
	  testAlgorithm(test, &insertion_sort);
	  testAlgorithm(test, &merge_sort);	  
	  testAlgorithm(test, &shell_sort1);
	  testAlgorithm(test, &shell_sort2);
	  testAlgorithm(test, &shell_sort3);
	  testAlgorithm(test, &shell_sort4);
	  testAlgorithm(test, &hybrid_sort1);	  
	  testAlgorithm(test, &hybrid_sort2);
	  testAlgorithm(test, &hybrid_sort3);	  
	}
	
	return 0;
}
