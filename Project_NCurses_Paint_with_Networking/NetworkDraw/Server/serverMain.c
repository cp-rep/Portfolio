// ============================================================================
// File: serverMain.c
// ============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "server01.h"
#include "serverCurses.h"

// macros
#define LEN		256
#define TRUE		1
#define FALSE 		0
#define DEBUG 		0



// ==== main  =================================================================
//
// ============================================================================
int main(void)
{
    // local variables
    auto ServerData		servData;
    auto ServerCurseData 	servCData;

    // start the server
    StartServer(&servData);

    // if server sets up curses without and error, enter
    if('z' == SetupServerCurses())
    {
        // setup server screen
        SetupServerScreen(&servCData);
	refresh();
	
	// tell client setup is successful
        servData.buf[0] = 'z';
	send(servData.client_socket, servData.buf, LEN, 0);
    }    
    
    else
    {
        exit(EXIT_FAILURE);
    }

    servData.buf[0] = 'm';
    // get client response that client setup was successful
    recv(servData.client_socket, servData.buf, LEN, 0);

    // if client was successful enter and begin drawing
    if('z' == servData.buf[0])
    {
        while(TRUE)
	{
	    servCData.m_servOption = 0;
	    servData.buf[0] = 0;
	    servData.num_client_bytes = 0;
            // update cursor position
	    move(servCData.m_servYCoord, servCData.m_servXCoord);
	    refresh();


	    // get user input
	    servData.num_client_bytes = recv(servData.client_socket, servData.buf, LEN, 0);
	    servCData.m_servOption = servData.buf[0];


	    if(servData.num_client_bytes)
	    {
	        printw("data input receieved");
	        // if input is alpha, change to upper-case
	        if((servCData.m_servOption >= 'a') && (servCData.m_servOption <= 'z'))
	        {
	            servCData.m_servOption = toupper(servCData.m_servOption);
	        }

                switch(servCData.m_servOption)
	        {
	            case KEY_UP:
	                mvwprintw(stdscr, --servCData.m_servYCoord
		    		        , servCData.m_servXCoord, " ");
	                refresh();
		        continue;
	            case KEY_DOWN:
                        mvwprintw(stdscr, ++servCData.m_servYCoord
		                        , servCData.m_servXCoord, " ");
	                refresh();
		        continue;
	            case KEY_LEFT:
 	                mvwprintw(stdscr, servCData.m_servYCoord
		                        , --servCData.m_servXCoord, " ");
	                refresh();
		        continue;
	            case KEY_RIGHT:
	                mvwprintw(stdscr, servCData.m_servYCoord
		                        , ++servCData.m_servXCoord, " ");
	                refresh();
		        continue;

		    #if DEBUG	    	   
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
	                // allow movement of cursor
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
		    #endif // DEBUG
		

	            default:
	            break;
		}
	    }
	    /*   
	    else
	    {
	        printw("Input from client to server do not match.");
		getch();
		break;
	    }
	    */
        } 
    }

    CloseServer(&servData);
    EndServerCurses();

    return 0;
} // end of "main"
