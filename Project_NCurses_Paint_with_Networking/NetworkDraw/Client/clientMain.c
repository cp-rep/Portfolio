// ============================================================================
// File: clientMain.c
// ============================================================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include "client01.h"
#include "clientCurses.h"

// macros
#define LEN		256
#define TRUE 		1
#define FALSE 		0



/*
typedef struct
{
   char			buf[LEN];
   int			client_socket;
   int			toServer;
   int 			fromServer;
   struct sockaddr_in 	client_address;
   char			userString[LEN];
}ClientData; 

typedef struct 
{
    int		m_clientMaxRows;
    int		m_clientMaxCols;
    int		m_clientYCoord;
    int		m_clientXCoord;
}ClientCurseData;
*/



// ==== main ==================================================================
//
// ============================================================================
int main(void)
{
    // local variables
    auto ClientData		clientData;
    auto ClientCurseData 	clientCData;

    // start the client, define client data and connect to server
    StartClient(&clientData);

    // receive a true or false value from server representing successful 
    // start of curses
    recv(clientData.client_socket, clientData.buf, LEN, 0);

    // if server successfully initialized curses, enter
    if(clientData.buf[0] == 'z')
    {
        // setup client curses and screen
	SetupClientCurses();
        SetupClientScreen(&clientCData);

	// tell server if successful
	send(clientData.client_socket, clientData.buf, LEN, 0);
	printw("Server was successful.");
	refresh();
    }

    // else, server had an error starting curses
    else
    {
        // prompt and exit
    	printf("Server had an error setting up curses.\n");
	exit(EXIT_FAILURE); 
    }

    // begin drawing
    while(TRUE)
    {
         // update cursor position
	 move(clientCData.m_clientYCoord, clientCData.m_clientXCoord);
	 refresh();

	 // get user input
	 clientData.buf = wgetch(stdscr);
//	 clientData.buf[0] = clientCData.m_clientOption;
	 
	 // send user input to server
	 send(clientData.client_socket, clientData.buf, LEN, 0);

	 // if input is alpha, change to upper-case
	 if((clientCData.m_clientOption >= 'a') 
	     && (clientCData.m_clientOption <= 'z'))
	 {
	     clientCData.m_clientOption = toupper(clientCData.m_clientOption);
	 }

	 switch(clientData.buf)
	 {
	     case KEY_UP:
	         mvwprintw(stdscr, --clientCData.m_clientYCoord
		                 , clientCData.m_clientXCoord, " ");
		 refresh();
		 continue;
	     case KEY_DOWN:
	         mvwprintw(stdscr, ++clientCData.m_clientYCoord
		                 , clientCData.m_clientXCoord, " ");
		 refresh();
		 continue;
	     case KEY_LEFT:
	         mvwprintw(stdscr, clientCData.m_clientYCoord
		 		 , --clientCData.m_clientXCoord, " ");
		 refresh();
		 continue;
	     case KEY_RIGHT:
	         mvwprintw(stdscr, clientCData.m_clientYCoord
		 		 , ++clientCData.m_clientXCoord, " ");
		 refresh();
		 continue;
 	     default:
	         break;
	 }
    }
    
    // close client connection
    EndClient(&clientData);
    EndClientCurses();

    
    return 0;
} // end of "void"
