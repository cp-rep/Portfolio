// ============================================================================
// File: serverCurses.c
// ============================================================================
#include <curses.h>
#include <stdlib.h>
#include "serverCurses.h"

// macros
#define TRUE		1
#define FALSE		0
#define DEBUG		0



// ==== SetupServerCurses ===========================================================
//
// ============================================================================
int SetupServerCurses(void)
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
/*
    if(!has_color())
    {
        exit(EXIT_FAILURE);
    }
*/
    if(ERR == start_color())
    {
        exit(EXIT_FAILURE);
    }
    
    // if everything goes well, return TRUE
    return 'z';
} // end of "SetupCurses"



// ==== SetupServerScreen =====================================================
//
// ============================================================================
void SetupServerScreen(ServerCurseData *servCData)
{
    color_set(0, NULL);

    getmaxyx(stdscr, servCData->m_servMaxRows, servCData->m_servMaxCols);

    move(servCData->m_servMaxRows/2, servCData->m_servMaxCols/2);

    init_pair(1, 0, COLOR_RED);
    init_pair(2, 0, COLOR_BLUE);
    init_pair(3, 0, COLOR_BLACK);
    init_pair(4, 0, COLOR_GREEN);
    init_pair(5, 0, COLOR_CYAN);
    init_pair(6, 0, COLOR_MAGENTA);
    init_pair(7, 0, COLOR_YELLOW);
    init_pair(8, 0, COLOR_WHITE); 
    
    servCData->m_servYCoord = servCData->m_servMaxRows/2;
    servCData->m_servXCoord = servCData->m_servMaxCols/2;

    refresh();
} // end of "SetupServerScreen"



// ==== EndServerCurses =============================================================
//
// ============================================================================
void EndServerCurses(void)
{
    clear();
    endwin();
} // end of "EndCurses"