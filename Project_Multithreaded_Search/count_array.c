// ============================================================================
// File: count_array.c
// Project: CountArray Project
// 
// Description:
//     This file contains the function implementations for the count_array.h 
//     header file for the CountArray Project.
//     
// ============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "count_array.h"

// macros
#define BUF 256



// ==== ThreadFunc ============================================================
// This function traverses an array in search for target information.  The
// traversal is aided by the contents of the incoming ThreadInfo structure.
// All variables from the structure are used.  The first and last variables
// are used for the bounds of the array search.  Depending on the search
// parameters, each incoming ThreadInfo structure will inspect a proceeding
// range of indexes until all indexes have been checked.
//
//
// Input:
//	vptr		[IN] --	a void pointer that contains the address of an
//			     	pointer to a ThreadInfo structure that is 
//				dynamically allocated
//
// Output:
//	iptr		[OUT]--	the address of a dynamically allocated
//				ThreadInfo structure.  It contains an updated
//				variable for the number of target matches
//				found
// ============================================================================

void*   ThreadFunc(void  *vptr)
{
    // local variables
    auto ThreadInfo *iptr;

    // store address of the parameter to a pointer to a thread info structure
    iptr = vptr;
    
    // create and set new local variables to be used as lower and upper bounds
    // in a loop that searches for the target value
    auto int start = iptr->first;
    auto int end = iptr->last;

    // loop and search for target value
    for(; start <= end; start++)
    {
        if(iptr->target == iptr->array[start])
	{
	    printf("*** ThreadFunc: TARGET FOUND! thread #%d found %d" 
		   " at index %d...\n", iptr->threadNum, iptr->target
		     	      		                      , start);

	    // update total number of targets found in the current segment
	    iptr->numFound++;
	}
    }

    // display findings to STDOUT
    printf("*** ThreadFunc about to return: thread #%d: first = %d, last = %d"
           ", array = %p, target = %d, numfound = %d\n", iptr->threadNum
	      	      	  	       		     , iptr->first
						     , iptr->last
						     , iptr->array
						     , iptr->target
						     , iptr->numFound);

    // return the base address of the structure to the caller	     
    return iptr;
} // end of "ThreadFunc"



// ==== AllocArray ============================================================
// This function creates a dynamic array and populates it with random values
// according to its incoming parameters.  It then returns the address of that
// array back to the caller to be used later in the program.
//
// 
// Input:
//     elements		[IN] --	the max number of elements to have in the whole
//     			     	array
//
//     mRand		[IN] -- the maximum value that can be stored in any
//     			     	single index
//
// Output:
//     arrPtr		[OUT]--	the base address of the new populated,
//     				dynamically allocated array of integers
// ============================================================================

int*	AllocArray(int *elements, const int *mRand)
{
    // local variables
    auto int		*arrPtr;
    auto int		index;

    // create a dynamic array
    arrPtr = malloc(sizeof(int) * (*elements));

    // populate indexes with random values
    for(index = 0; index < *elements; index++)
    {
        arrPtr[index] = (rand() % ((*mRand) + 1));
    }

    // return the base address of the array
    return arrPtr;
} // end of "AllocArray"



// ==== GetUserIn =============================================================
// This function prompts the and gets any necessary information from the user
// for creating and searching the array.
//
// Input:
//     elems		[IN] --	the total number of elements for the array
//
//     maxRan		[IN] -- the maximum integer value that any array index
//     			     	contain
//
//     segs		[IN] -- the number of segments to break the array into
//     			     	which will be used for individual threads
//
//     mThreads		[IN] -- the total number of threads to use for the
//     			     	target search
//
//     targ		[IN] -- the target value to search for in the array
//
// Ouput:
//     NONE
//
// ============================================================================

void	GetUserIn(int *elems, int *maxRan, int *segs, const int *mThreads
		      	      	  	       	      	    , int *targ)
{
    // Prompt and get all user input for the program
    printf("Please enter the total number of elements: ");
    if(!scanf("%d", elems))
    {
        printf("GetUserIn: error reading thenumber of elements.\n");
	exit(EXIT_FAILURE);
    }

    printf("Please enter the maximum random value: ");
    if(!scanf("%d", maxRan))
    {
        printf("Error reading the maximum random value\n");
	exit(EXIT_FAILURE);
    }

    printf("Please enter the number of segments (1 to %d): ", *mThreads);
    if(!scanf("%d", segs))
    {
        printf("Invalid Input.\n");
	exit(EXIT_FAILURE);
    }

    else if(*segs > *mThreads)
    {
        printf("\nSorry, that exceeds the thread limit...\n");
	exit(EXIT_FAILURE);
    }


    // get the target value to look for
    printf("Please enter the target value: ");
    if(!scanf(" %d", targ))
    {
        printf("Error reading target.\n");
	exit(EXIT_FAILURE);
    }

} // end of "GetUserIn"



// ==== GetMaxThreads =========================================================
// This function opens a file that contains the number of allowed threads that
// can be used from the school server and extracts that data into a variable.
//
// Input:
//     NONE
//
// Output:
//     mThread		[OUT]--	The number of threads read from file
// 
// ============================================================================

int	GetMaxThreads()
{
    // local variables
    auto    FILE		*inFile;
    auto    int			inChar;
    auto    int			charCount = 0;
    auto    char		charArr[BUF];
    auto    int			mThread;

    // open file containing threads on server
    inFile = fopen("/proc/sys/kernel/threads-max", "r");

    // check for success on open
    if(NULL == inFile)
    {
        printf("Failed to open file.\n");
	exit(EXIT_FAILURE);
    } 

    // read data into a character string
    while(EOF != (inChar = fgetc(inFile)))
    {        
        charArr[charCount] = inChar;
	charCount++;
    }

    // convert the string into an integer
    sscanf(charArr, "%d", &mThread);

    // close input file
    fclose(inFile);

    // return the number of threads
    return mThread;

} // end of "GetMaxThreads"



// ==== OptValues =============================================================
// This function changes any necessary values before they are used in any
// other program statements so that other program statements can use them
// as intended.
//
// Input:
//     nEls		[IN] --	the total number of elements in the integer
//     			     	array
//
//     nSegs		[IN] -- the number of segments the user entered,
//     			        representing the number of threads to use in
//				the target search
//
//     nSegEls		[IN] --	the number of elements that each segment will
//     			     	be broken into for each thread
//    
//     start		[IN] -- the starting index for a segment
//
//     end		[IN] --	the ending index for a segment
//
// Output:
//     NONE
//     
// ============================================================================

void    OptValues(const int *nEls, int *nSegs, int *nSegEls, int *start
							     , int *end)
{
    // local variables
    auto int n;
    
    n = *nEls;

    // correct the number of segments in order to not allow there to be more
    // more segments than elements
    while(*nEls < *nSegs)
    {
         *nSegs -= 1;
    }
    
    // calculate how many elements should be in each segment
    *nSegEls = n / *nSegs;

    // set the initial starting index in the search
    *start = 0;

    // set the ending index for the first segment in the search
    *end = *nSegEls - 1;

} // end of "OptValues"