#define _POSIX_SOURCE
#define _DEFAULT_SOURCE

#include "event.h"

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>

#define SERVER_IP "0.0.0.0"
#define SERVER_PORT 7000

int create_outgoing_socket();

int create_incoming_socket();

struct sockaddr_in create_address(char* ip, int port);

int receive_key_event(struct key_event_packet* event, int socket_fd);

int send_key_event(struct key_event_packet* event, struct sockaddr_in* addr, int socket_fd);
