/* udptalkc.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    int sockfd, nbytes, port, addrlen;
    char buf[1024];
    struct sockaddr_in srvaddr;
    
    if(argc != 3){
        printf("usage: %s hostname port", argv[0]);
        return -1;
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("create socket error.");
        return -2;
    }
    port = atoi(argv[2]);
    bzero(&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(port);
    srvaddr.sin_addr.s_addr = inet_addr(argv[1]);

    while(1) {
        addrlen = sizeof(struct sockaddr);
        nbytes = read(STDIN_FILENO, buf, 1024);
        sendto(sockfd, buf, nbytes, 0,
               (struct sockaddr *)&srvaddr, addrlen);
        nbytes = recvfrom(sockfd, buf, 1024, 0,
                 (struct sockaddr *)&srvaddr, &addrlen);
        write(STDOUT_FILENO, buf, nbytes);
    }
    close(sockfd);

    return 0;
}
