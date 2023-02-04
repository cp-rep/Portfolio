// ============================================================================
// File: clientCurses.c
// ============================================================================
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include "clientCurses.h"


// macros
#define TRUE		1
#define FALSE		0
#define DEBUG		0


/*
typedef struct 
{
    int		m_clientMaxRows;
    int		m_clientMaxCols;
    int		m_clientYCoord;
    int		m_clientXCoord;
}ClientCurseData;
*/


// ==== SetupClientCurses =====================================================
//
// ============================================================================
int SetupClientCurses(void)
{
    if(NULL == initscr())
    {
        exit(EXIT_FAILURE);
    }

    if(ERR == noecho())
    {
        exit(EXIT_FAILURE);
    }

    if(ERR == cbreak())
    {
        exit(EXIT_FAILURE);
    }

    if(ERR == curs_set(TRUE))
    {
        exit(EXIT_FAILURE);
    }

    if(ERR == keypad(stdscr, TRUE))
    {
        exit(EXIT_FAILURE);
    }

    if(ERR == start_color())
    {
        exit(EXIT_FAILURE);
    }

    // if everything goes well, return TRUE
    return 'z';
    
} // end of "SetupClientCurses"



// ==== SetupClientScreen =====================================================
//
// ============================================================================
void SetupClientScreen(ClientCurseData *clientCData)
{
    // set starting color of curses screen
    color_set(0, NULL);

    // get information about user screen
    getmaxyx(stdscr, clientCData->m_clientMaxRows
		   , clientCData->m_clientMaxCols);

    // move the cursor to the center of the curses screen
    move(clientCData->m_clientMaxRows/2, clientCData->m_clientMaxCols/2);
    
    // create color pairs
    init_pair(1, 0, COLOR_RED);
    init_pair(2, 0, COLOR_BLUE);
    init_pair(3, 0, COLOR_BLACK);
    init_pair(4, 0, COLOR_GREEN);
    init_pair(5, 0, COLOR_CYAN);
    init_pair(6, 0, COLOR_MAGENTA);
    init_pair(7, 0, COLOR_YELLOW);
    init_pair(8, 0, COLOR_WHITE);

    clientCData->m_clientYCoord = clientCData->m_clientMaxRows/2;
    clientCData->m_clientXCoord = clientCData->m_clientMaxRows/2;

    refresh();
} // end of "SetupClientScreen"

 

// ==== EndClientCurses =======================================================
//
// ============================================================================
void EndClientCurses(void)
{
    clear();
    endwin();
} // end of "EndClientCurses"
