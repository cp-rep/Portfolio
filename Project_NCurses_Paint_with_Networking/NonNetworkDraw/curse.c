// ============================================================================
// File: curse.c
// 
// Description:
//     This is the implementation file for the curse.h header file.
//
// ============================================================================
#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include "curse.h"

// macros
#define TRUE 1
#define FALSE 0
#define DEBUG 0



// colors (some may be inaccurate)
#define BLUE		0x01
#define GREEN 		0x02
#define RED		0x04
#define YELLOW		0x08
#define BLACK		0x10
#define WHITE		0x20
#define CYAN		0x40
#define MAGENTA		0x80



// ==== BeginCursesSession ====================================================
//
// Description:
//     This function sets up and starts necessary routines for ncurses to
//     function as desired for the draw program.  When each routine is called
//     they are checked for a successful return value, else the program
//     will close and prompt stdout with the reason for exiting.
//          
//
// Input:
//     NONE
//
// Output:
//     int		[OUT]-	a value representing either a successful
//     				exececution of all progrma statements,
//				or a failure value.
// ============================================================================
int	BeginCursesSession()
{
    // initialize curses data structures
    if(NULL == initscr()) 
    {
        return INIT_FAILED;
    }

    // disable echoing of stdin buffer
    if(ERR == noecho())
    {
	return NOECHO_FAILED;
    }

    // allow interrupt and flow control control commands
    if(ERR == cbreak())
    {
        return CBREAK_FAILED;
    }

    // show cursor
    if(ERR == curs_set(TRUE))
    {
        return CBREAK_FAILED;
    }
    
    // enable keypad routines
    if(ERR == keypad(stdscr, TRUE))
    {
        return KEYPAD_FAILED;
    }

    if(FALSE == has_colors())
    {
        return COLOR_FAILED;    
    }

    if(ERR == start_color())
    {
        return COLOR_FAILED;
    }

    // return no errors
    return FALSE;
} // end of "BeginCursesSession"



// ==== SetColorPairs ========================================================
//
// Description:
//     This function creates color pairs that can be called through out the  
//     program.  It then sets a starting color for the program; which is no
//     color.
//
// Input:
//     NONE
//
// Output:
//     int		[OUT]- a value representing succesful execution of
//     			       program statements
// ============================================================================
int	SetColorPairs()
{
    // create color pairs
    init_pair(1, 0, RED);
    init_pair(2, 0, BLUE);
    init_pair(3, 0, BLACK);
    init_pair(4, 0, GREEN);
    init_pair(5, 0, COLOR_CYAN);
    init_pair(6, 0, MAGENTA);
    init_pair(7, 0, COLOR_YELLOW);
    init_pair(8, 0, COLOR_WHITE); 

    // give a starting color pair (no color)
    color_set(0, NULL);

    // return no errors
    return FALSE;
  
} // end of "SetColorPairs"



// ==== SetupScreen ===========================================================
//
// Description:
//     This function gets necessary information for dertmining the users
//     screen information.  It then uses this information to coordinate
//     placement of the cursor, and also to define values used as row and
//     column numbers through out further program statements in the program.
//
// Input:
//     *data		[OUT]- a pointer to a CurseData structure.  The curse
//     			       data structure contains information for 
//			       the stdscr window being used, as well as
//			       a value for determining user input.
//
// Output:
//     NONE
// ============================================================================
void	SetupScreen(CurseData *data)
{
    // get screen information and position cursor
    getmaxyx(stdscr, data->m_maxRows, data->m_maxCols);

    // get current cursor position for center of screen
    data->m_screenCursorY = data->m_maxRows/2;
    data->m_screenCursorX = data->m_maxCols/2;

    // move cursor to center of screen
    move(data->m_screenCursorY, data->m_screenCursorX);
    refresh();

    // create the tool menu window
    CreateToolMenu(data);

} // end of "SetupScreen"



// ==== CreateToolMenu ========================================================
//
// ============================================================================
int	 CreateToolMenu(CurseData *data)
{
    // create tool menu box    
    data->toolWin = newwin(7, data->m_maxCols - 12, data->m_maxRows - 8, 5);
    box(data->toolWin, 0, 0);
 
    // get tool menu cursor position
    data->m_toolMenuCursorY = data->m_maxRows - 7;
    data->m_toolMenuCursorX = 7;

    // define string names for tool choices
    data->m_options {"Draw", "Erase", "Red", "Blue", "Black", "Yellow"
    		     	         , "Green", "Magenta", "Cyan", "White"};

    //

    // refresh changes to window
    refresh();
    wrefresh(data->toolWin);
    
} // end of "CreateToolMenu"



// ==== EndCurses =============================================================
// Description:
//     When this function is called the active window is cleared and then
//     any stored curses data is released from memory.
//
// Input:
//     NONE
//
// Output:
//     NONE
// ============================================================================
void    EndCurses()
{ 
    // clear screen and free curses data from memory
    clear();
    endwin();
} // end of "EndCurses"



// ==== BeginDrawing ==========================================================
// Description:
//     This is the primary function that loops throughout the program allowing
//     the user to draw and modify the current color pair that is set.
//
// Input:
//     *incData		[OUT]- a pointer to a CurseData structure.  The curse
//     			       data structure contains information for 
//			       the stdscr window being used, as well as
//			       a value for determining user input.
//
// Output:
//     NONE
// ============================================================================
void	BeginDrawing(CurseData *data)
{
    // switch between movement and color changes
    while(TRUE) 
    {	
    	// update cursor position
        move(data->m_screenCursorY, data->m_screenCursorX);
	refresh();

	// get user input
        data->m_option = wgetch(stdscr);

	// if input is alpha, change to upper-case
	if((data->m_option >= 'a') && (data->m_option <= 'z'))
	{
	    data->m_option = toupper(data->m_option);
	}

        switch(data->m_option)
	{
	    case KEY_UP:
	        mvwprintw(stdscr, --data->m_screenCursorY
		                , data->m_screenCursorX, " ");
	        refresh();
		continue;
	    case KEY_DOWN:
                mvwprintw(stdscr, ++data->m_screenCursorY
				, data->m_screenCursorX, " ");
	        refresh();
		continue;
	    case KEY_LEFT:
 	        mvwprintw(stdscr, data->m_screenCursorY
				, --data->m_screenCursorX, " ");
	        refresh();
		continue;
	    case KEY_RIGHT:
	        mvwprintw(stdscr, data->m_screenCursorY
		                , ++data->m_screenCursorX, " ");
	        refresh();
		continue;
	    case 'T':
	        // call the tool menu
	        ChangeTool(data);
		refresh();
		wrefresh(data->toolWin);
		continue;
            case 'R':
	        // red
	        color_set(2, NULL);
		continue;
	    case 'L':
	        // black
	        color_set(3, NULL);
		continue;
	    case 'G':
	        // green
	        color_set(4, NULL);
		continue;
	    case 'B':
	        // blue
	        color_set(1, NULL);
		continue;
            case 'Y':
	        // yellow
	        color_set(7, NULL);
		continue;
            case 'O':
	        // default color
		color_set(0, NULL);
		continue;
	    case 'M':
	        // magenta
	        color_set(6, NULL);
		continue;
	    case 'W':
	        // white
	        color_set(8, NULL);
		continue;
	    case 'C':
	        // cyan
	        color_set(5, NULL);
		continue;
	    default:
	        break;
	}
    }
} // end of "BeginDrawing"



// ==== ErrorMenu =============================================================
// Description:
//     This function outputs useful error information to stdout. If there is
//     any problem with the main functionality of curses this function is 
//     called.  The error values are generated from an enumeration structure
//     defined at the top of the source code.
//
// Input:
//     errorVal		[IN] - an integer value representing the error value
//     			       receieved from another function.
//
// Output:
//     int		[OUT]- A value of -1 if the error is contained in a
//     			       program statement of the switch structure, 0
//     			       otherwise.
// ============================================================================
int	ErrorMenu(short errorVal)
{
    switch(errorVal)
    {
        case SUCCESS:
	    EndCurses();
	    return TRUE;
	case INIT_FAILED:
	    EndCurses();
	    #if DEBUG
	    printf("errorVal: %d\n" , errorVal);
	    #endif // DEBUG
	    printf("Error: Failed to initialize standard screen.\n");
	    return ERR;
	case NOECHO_FAILED:
	    EndCurses();
	    #if DEBUG
	    printf("errorVal: %d\n" , errorVal);
	    #endif // DEBUG
	    printf("Error: noecho().\n");
	    return ERR;
	case CBREAK_FAILED:
	    EndCurses();
	    #if DEBUG
	    printf("errorVal: %d\n" , errorVal);
	    #endif // DEBUG
	    printf("Error: cbreak().\n");
	    return ERR;
	case CURSOR_FAILED:
	    EndCurses();
	    #if DEBUG
	    printf("errorVal: %d\n" , errorVal);
	    #endif // DEBUG
	    printf("Error: curs_set().\n");
	    return ERR;
	case KEYPAD_FAILED:
	    EndCurses();
	    #if DEBUG
	    printf("errorVal: %d\n" , errorVal);
	    #endif // DEBUG
	    printf("Error: keypad().\n");
	    return ERR;
	case COLOR_FAILED:
	    EndCurses();
	    #if DEBUG
	    printf("errorVal: %d\n" , errorVal);
	    #endif // DEBUG
	    printf("Error: color failed.\n");
	    return ERR;
	default:
	    return FALSE;
    }    
} // end of "ErrorMenu"



// ==== ChangeTool ============================================================
//
// ============================================================================
void	ChangeTool(CurseData *data)
{
    
} // end of "ChangeTool"