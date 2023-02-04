// ============================================================================
// File: server01.h
// ============================================================================
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

// macros
#define LEN 256

#ifndef SERVER01_H
#define SERVER01_H

typedef struct{
    char		buf[LEN];
    int			server_socket;
    int			client_socket;
    socklen_t		client_len;
    ssize_t		num_client_bytes;
    struct sockaddr_in	client_address;
    struct sockaddr_in	server_address;
}ServerData;
 
// function prototypes
void StartServer(ServerData *sData);
void CloseServer(ServerData *serData);


#endif //SERVER01_H

