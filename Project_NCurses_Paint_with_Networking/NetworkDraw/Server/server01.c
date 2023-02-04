// ============================================================================
// File: server01.c
// ============================================================================
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include "server01.h"

// macros
#define LEN 256
#define SOCKET_NAME "server_socket"
#define TRUE 1
#define FALSE 0
#define PORT 50005



// ==== StartServer ===========================================================
//
// ============================================================================
void StartServer(ServerData *sData)
{
    // remove any existing socket, create a new unnamed socket for the server
    sData->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sData->server_socket)
    {
        perror("server -- socket failed");
	exit(EXIT_FAILURE);
    }

    // bind the socket to a name
    memset(&sData->server_address, 0, sizeof(sData->server_address));
    sData->server_address.sin_family = AF_INET;
    sData->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    sData->server_address.sin_port = htons(PORT);

    // test for successful bind
    if(bind(sData->server_socket, (struct sockaddr*)&sData->server_address
						, sizeof(sData->server_address)))
    {
	perror("server -- bind failed");
    }
					
    // create connection queue and wait for a client				
    if(listen(sData->server_socket, 5))
    {
        perror("server -- listen failed");
    }

    // announce server is waiting for client connection
    puts("server waiting...");

    // accept a connection
    sData->client_len = sizeof(sData->client_address);
    sData->client_socket = accept(sData->server_socket
    			   , (struct sockaddr*)&sData->client_address
		    	         		, &sData->client_len);

} // end of "main"



// ==== StartServer ===========================================================
//
// ============================================================================
void CloseServer(ServerData *serData)
{
    close(serData->client_socket);
    close(serData->server_socket);
} // end of "CloseServer"