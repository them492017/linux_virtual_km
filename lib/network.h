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

int create_socket();

int receive_key_event(struct key_event_packet* event, int socket_fd);
