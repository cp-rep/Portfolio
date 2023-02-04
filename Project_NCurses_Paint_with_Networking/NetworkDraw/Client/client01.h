// ============================================================================
// File: client01.h
// ============================================================================
#include <netinet/in.h>

// macros
#define LEN 256

// guard against nested includes
#ifndef CLIENT01_H
#define CLIENT01_H

typedef struct
{
    char		buf[LEN];
    int			client_socket;
    struct sockaddr_in 	client_address;
}ClientData; 

// function prototypes
void StartClient(ClientData *data);
void EndClient(ClientData *cliData);

#endif // CLIENT01_H



