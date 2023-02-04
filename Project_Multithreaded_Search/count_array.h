// ============================================================================
// File: count_array.h (Spring 2017)
// Project: CountArray Project
//
// Description:
//	The header file for the CountArray Project. It contains a structure
//	declaration and any function prototypes. 
// ============================================================================

#ifndef COUNT_ARRAY_H
#define COUNT_ARRAY_H


// structure declarations
typedef struct
{
    int     threadNum;
    int     *array;
    int     first;
    int     last;
    int     target;
    int     numFound;

} ThreadInfo;


// function prototypes
int	GetMaxThreads();
void*   ThreadFunc(void  *vptr);
int*	AllocArray(int *elements, const int *mRand);
void	GetUserIn(int *elems, int *maxRan, int *segs, const int *mThreads
		      	      	  	       	      	    , int *targ);
void    OptValues(const int *nEls, int *nSegs, int *nSegEls, int *start
			    	       	       	   	     , int *end);

#endif  // COUNT_ARRAY_H
