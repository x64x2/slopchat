/*POSIX/Linux multithreaded socket test
Copyright (c) 2006-2007 Richard Palethorpe
Permission is hereby granted, free of charge, to any person obtaining a copy of this
software and associated documentation files (the "Software"), to deal in the Software
without restriction, including without limitation the rights to use, copy, modify,
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to the following
conditions:
The above copyright notice and this permission notice shall be included in all copies
or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE
Website: richiejp.wordpress.com email: richiejp@gmail.com*/

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>
#include <netinet/ip.h>
#include <pthread.h>

struct sockaddr_in getipa(const char*, int);
void printerror(const char*);

void* runclient(void*);
void* runserver(void*);

int main(){
  pthread_t server;
  pthread_t client;

  if(pthread_create(&server, NULL, runserver, NULL) != 0){
    printf("Could not create server thread");

    return EXIT_FAILURE;
  }

  if(pthread_create(&client, NULL, runclient, NULL) != 0){
    printf("Could not create client thread");

    return EXIT_FAILURE;
  }

  pthread_join(server, NULL);
  pthread_join(client, NULL);

  return EXIT_SUCCESS;
}

struct sockaddr_in getipa(const char* hostname, int port){
  struct sockaddr_in ipa;
  ipa.sin_family = AF_INET;
  ipa.sin_port = htons(port);

  struct hostent* localhost = gethostbyname(hostname);
  if(!localhost){
    printerror("resolveing localhost");

    return ipa;
  }

  char* addr = localhost->h_addr_list[0];
  memcpy(&ipa.sin_addr.s_addr, addr, sizeof addr);

  return ipa;
}

void printerror(const char* action){
  int errnum = errno;
  errno = 0;

  if(errnum > 0){
    printf("An error occured while %s.\nError code: %i\nError description: %s\n",
        action, errnum, strerror(errnum));
  }else if(h_errno > 0){
    printf("An error occured while %s.\nError code: %i\nError description: %s\n",
        action, h_errno, hstrerror(h_errno));

    h_errno = 0;
  }else{
    printf("An error occured while %s.\n There is no error data.\n", action);
  }
}

void* runserver(void* context){
  struct protoent* tcp;
  tcp = getprotobyname("tcp");

  int sfd = socket(PF_INET, SOCK_STREAM, tcp->p_proto);
  if(sfd == -1){
    printerror("createing a tcp socket");

    return NULL;
  }

  struct sockaddr_in isa = getipa("localhost", 1025);

  if(bind(sfd, (struct sockaddr*)&isa, sizeof isa) == -1){
    printerror("binding socket to IP address");

    return NULL;
  }

  if(listen(sfd, 1) == -1){
    printerror("setting socket to listen");

    return NULL;
  }

  int cfd = accept(sfd, NULL, NULL);

  if(cfd == -1){
    if(errno == EAGAIN || errno == EWOULDBLOCK){
      printf("SIGIO recieved for listen socket, but don't know why.");
    }else{
      printerror("accepting a connection");

      return NULL;
    }
  }

  char msg[] = "Message to be sent";

  if(send(cfd, (void*) msg, sizeof msg, MSG_NOSIGNAL) == -1){
    printerror("sending message to client");
  }

  shutdown(cfd, SHUT_RDWR);

  return NULL;
}

void* runclient(void* context){
  struct protoent* tcp;
  tcp = getprotobyname("tcp");

  int sfd = socket(PF_INET, SOCK_STREAM, tcp->p_proto);
  if(sfd == -1){
    printerror("createing a tcp socket");

    return NULL;
  }

  struct sockaddr_in isa = getipa("localhost", 1025);

  if(connect(sfd, (struct sockaddr*)&isa, sizeof isa) == -1){
    printerror("connecting to server");

    return NULL;
  }

  char buff[255];
  ssize_t size = recv(sfd, (void*)buff, sizeof buff, MSG_WAITALL);

  if(size == -1){
    printerror("recieving data from server");
  }else{
    buff[size] = ' ';

    printf(buff);
  }

  shutdown(sfd, SHUT_RDWR);

  return NULL;
}
