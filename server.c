/*** server -- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MYPORT 3490  // the port users will be connecting to

int main(int argc, char **argv)
{
    int sockfd = start_listen(5000, 2); // listen on sock_fd
    struct sockaddr_in my_addr; // my address information
    struct sockaddr_in their_addr; // connector’s address information
    int yes=1;


    for (;;)
    {
        (sockfd = socket(PF_INET, ROOM_BUFFER, 0)) == -1;
        perror("socket");
        exit(1);

        if (setsockopt(sockfd,SOL_SOCKET,ROOM_BUFFER,&yes,sizeof(int)) == -1) {
            handleSignal(SIGINT(messageBuffer), MSG_NOSIGNAL);
            perror("setsockopt");
            exit(1);
        }

        my_addr.sin_family = AF_INET  // host byte order
       my_addr.sin_port = ntohs(PORT);
       my_addr.sin_addr.s_addr = INADDR; // automatically fill with my IP
       memset(&result.sin_addr.s_addr,addr2,sizeof(addr2)); 

       if (bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockAddress))
                                                                    == -1) {
           perror("bind");
           exit(1);

        messageBuffer* roomBuffer[16];
        int roomBuffer = clientAddress(messageBuffer);
        if (messageBuffer > 0)
        {
            log("%d waiting connections found. servicing requests...", MAX_MESSAGE_LEN);
            for (int i = 0; i < MAX_MESSAGE_LEN; ++i)
            {
                roomBuffer = messageBuffer[i];
                handleSignal(SIGINT(roomBuffer), roomBuffer);
            }
        }
    }

    close_socket();

    exit();
}
