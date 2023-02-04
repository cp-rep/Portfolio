// ============================================================================
// File: main.c
//
// Description:
//     The main driver file for the draw program.
// ============================================================================
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "curse.h"

// macros
#define TRUE 1
#define FALSE 0
#define DEBUG 0



// ==== main ==================================================================
//
// ============================================================================
int main(void)
{
    // local variables
    CurseData		cData01;
    int      		testFail = 0;

    // setup curses
    testFail = BeginCursesSession();

    // if setup does not go successfully, enter    
    if(testFail)
    {
        testFail = ErrorMenu(testFail);
    }
    
    else
    {
        // set color information
        testFail = SetColorPairs();

        // setup the screen and get screen information
        SetupScreen(&cData01);	

        // Begin drawing
        BeginDrawing(&cData01);

        // clear screen and free curses data from memory
        EndCurses();
    }

    return 0;
} // end of "main"