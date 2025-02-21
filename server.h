#pragma once

#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>

#include "../../libslopchat/include/libslopchat.h"
#include "users.h"
#include "rooms.h"

#define DEFAULT_LISTEN_PORT 5000

extern LIST_HEAD(UserList, ListElementUser) *users;

Session *await_response(int socket_desc, struct sockaddr_in *remote_addr);

int start_listen(int port, int queue_size);

void init();

void init_rooms();

/*
 * Check if any of the clients currently connected to the server have sent
 * a message and return its Session if there is.
 * If there are no pending messages, return NULL.
 */
int poll_clients(Session *out_waiting_sessions[]);
