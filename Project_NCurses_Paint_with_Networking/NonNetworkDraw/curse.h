// ============================================================================
// File: curse.h
// 
// Description:
//     This file is the header file for the file curse.c.  It contains any 
//     function prototypes and structure declarations.
//
// ============================================================================
#include <curses.h>
#ifndef CURSE_H
#define CURSE_H

// enum list used for displaying errors to stdout
enum EXIT_STATUS
{
    SUCCESS,			// 0
    INIT_FAILED,		// 1
    NOECHO_FAILED,		// 2
    CBREAK_FAILED, 		// 3
    CURSOR_FAILED,		// 4
    KEYPAD_FAILED,		// 5
    COLOR_FAILED,		// 6    
};



// enum list used for changing or displaying toolbar attributes
enum TOOL_OPTIONS
{
    DEFAULT,			// 0
};



// ==== CurseData =============================================================
//
//     ** Screen Variables **
//     m_maxRows		- stdscr, max y value
//     m_maxCols		- stdscr, max x value
//
//     ** User Input **
//     m_option
//
//     ** Cursor Variables **
//     m_screenCursorY	
//     m_screenCursorX	
//     m_toolMenuCursorY	
//     m_toolMenuCursorX
//
//     ** Windows **
//     toolWin
// ============================================================================
typedef struct
{
    // member variables
    int			m_maxRows;
    int			m_maxCols;
    int			m_option;
    int			m_screenCursorY;
    int			m_screenCursorX;
    int			m_toolMenuCursorY;
    int			m_toolMenuCursorX;
    WINDOW*		toolWin;
    string		m_options[16];
}CurseData;



// curse function prototypes
int	 BeginCursesSession();
int	 SetColorPairs();
void	 SetupScreen(CurseData *data);
void     EndCurses();
void	 BeginDrawing(CurseData *data);
int	 ErrorMenu(short errorVal);
void	 ChangeTool(CurseData *data);
int	 CreateToolMenu(CurseData *data);	

#endif // CURSE_H