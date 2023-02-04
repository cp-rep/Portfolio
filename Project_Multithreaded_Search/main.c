// ============================================================================
// File: main.c (Spring 2017)
// Project: CountArray Project
//
// Description:
//     This program is an example of a multi-threaded search.  It gets user
//     input for a size, target, and maximum value for a dynamic array and
//     then populates the array according to those parameters. It then takes 
//     user input for how many threads the user would like to use in searching 
//     the array for a target value.  When the search is finished, it will 
//     display all results to STDOUT and then return to the operating system.
// ============================================================================
#include    <pthread.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    "count_array.h"



// ==== main ==================================================================
// 
// ============================================================================

int     main(void)
{
    // local variables
    auto    int                 numSegs;
    auto    int                 numSegElems;
    auto    int                 target;
    auto    int                 totalElems;
    auto    int                 totalFound = 0;
    auto    ThreadInfo          *infoPtr;
    auto    pthread_t           *threadHandles;
    auto    int		        *intArr;
    auto    int			maxRandom;
    auto    int			beginning;
    auto    int			finish;
    auto    int			maxThreads;

    // get max thread number
    maxThreads = GetMaxThreads();
    
    // get user input
    GetUserIn(&totalElems,&maxRandom, &numSegs, &maxThreads, &target);

    // configure the array to work with
    intArr = AllocArray(&totalElems, &maxRandom);

    // correct/optimize any values before use						
    OptValues(&totalElems, &numSegs, &numSegElems, &beginning, &finish);    

    // display initial information
    printf("*** Begin search: target = %d, # elements = %d, # segments = %d, "
                                                "# segment elements = %d\n"
                                                                , target
                                                                , totalElems
                                                                , numSegs
                                                                , numSegElems);

    // allocate an array to store the thread handles
    threadHandles = malloc(sizeof(pthread_t) * numSegs);

    // create an array for storing the addresses of all ThreadInfo structures
    auto    ThreadInfo		*info[numSegs];

    // loop and create threads
    for(int index = 0; index < numSegs; index++)
    {    
        // allocate a thread info structure from the heap
	infoPtr = malloc(sizeof(ThreadInfo));
	info[index] = infoPtr;
        
        // store the information in the allocated structure
	infoPtr->threadNum = index;
	infoPtr->array = intArr;
	infoPtr->target = target;
	infoPtr->numFound = 0;
	infoPtr->first = beginning;
	if(index == (numSegs -1))
	{
	    finish = totalElems - 1;
	}
	infoPtr->last = finish;
	
        // create the secondary thread, passing the thread info
	if(pthread_create(&threadHandles[index], NULL, ThreadFunc, infoPtr))
	{
	    fprintf(stderr, "ERROR: Failed to create secondary thread!\n");
	}

	// update indexes for the next ThreadInfo structure
	beginning += numSegElems;
	finish += numSegElems;
    }

    // loop and join the threads to fetch each thread's results
    for(int index = 0;index < numSegs; index++) 
    {
        // join with the next thread
	if(pthread_join(threadHandles[index], (void*)&infoPtr))
	{
	    fprintf(stderr, "main: call to pthread_join failed,"
	    		    	   " counter = %d\n", infoPtr->threadNum);
	}

        // get the total number of matches from the thread's infoPtr
        // and display a message
	else
	{
	    printf("*** pthread_join returned: threadNum = %d, numFound = %d\n"
	                                                 , infoPtr->threadNum
							 , infoPtr->numFound);
        }						

	// update total target matches received from threads
  	totalFound += infoPtr->numFound;

        // release the infoPtr structure back to the heap
	free(info[index]);
	info[index] = NULL;

    }

    // display the final results!
    printf("*** Total matches found = %d\n", totalFound);
    
    // release heap memory
    free(threadHandles);
    threadHandles = NULL;
    free(intArr);
    intArr = NULL;

    return 0;

}  // end of "main"