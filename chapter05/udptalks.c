/* udptalks.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERV_PORT   5678

int main(int argc, char *argv[])
{
    int sockfd, nbytes, addrlen;
    char buf[1024];
    struct sockaddr_in srvaddr, cliaddr;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("create socket error.");
        return -1;
    }

    bzero(&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(SERV_PORT);
    srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    addrlen = sizeof(struct sockaddr);

    if(bind(sockfd, (struct sockaddr *)&srvaddr,
            addrlen) == -1) {
                perror("bind error.");
                return -2;
    }

    while(1) {
        addrlen = sizeof(struct sockaddr);
        nbytes = recvfrom(sockfd, buf, 1024, 0,
                 (struct sockaddr *)&cliaddr, &addrlen);
        write(STDOUT_FILENO, buf, nbytes);
        nbytes = read(STDIN_FILENO, buf, 1024);
        sendto(sockfd, buf, nbytes, 0,
            (struct sockaddr *)&cliaddr, addrlen);
    }

    close(sockfd);

    return 0;
}
