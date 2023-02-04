// ============================================================================
// File: client01.c
// ============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client01.h"

// macros
#define LEN		256
#define SOCKET_NAME	"server_socket"
#define TRUE 		1
#define FALSE 		0
#define SERVER_PORT 	50005



// ==== StartClient ===========================================================
//
// ============================================================================
void StartClient(ClientData *data)
{
    // create socket
    data->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == data->client_socket)
    {
        perror("client -- socket failed");
	exit(EXIT_FAILURE);
    }

    // bind the socket to a name
    memset(&data->client_address, 0, sizeof(data->client_address));
    data->client_address.sin_family = AF_INET;
    data->client_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    data->client_address.sin_port = htons(SERVER_PORT);
 
    // request a connection to server
    if(connect(data->client_socket, (struct sockaddr*)&data->client_address
    				    	    , sizeof(data->client_address)))
    {
        perror("client -- failed to connect...");
	exit(EXIT_FAILURE);
    }
    
    // prompt a successful connection
    else
    {
        printf("Connected...\n");
    }

} // end of "main"



// ==== EndClient =============================================================
//
// ============================================================================
void EndClient(ClientData *cliData)
{
    close(cliData->client_socket);
} // end of "EndClient"