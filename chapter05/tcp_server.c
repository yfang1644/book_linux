/* tcp_server.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define SERV_PORT       5678
int main(int argc ,char *argv [])
{
    int sockfd, connfd, nbytes, addrlen;
    char buf[1024];
    struct sockaddr_in srvaddr, cliaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("create socket error.");
        return -1;
    }

    bzero(&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(SERV_PORT);
    srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    addrlen = sizeof(struct sockaddr);

    if(bind(sockfd, (struct sockaddr *)&srvaddr ,
            addrlen ) == -1) {
                perror("bind error.");
                return -2;
            }

    if(listen(sockfd, 5) == -1 ) {
        perror("listen error.");
        return -3;
    }

    if(connfd = accept(sockfd, (struct sockaddr *)&cliaddr ,
                       &addrlen) < 0 ) {
                           perror("accept error.");
                           return -4;
                       }

    printf("server : got connection from %s, port %d\n",
           inet_ntoa(cliaddr.sin_addr), htons(cliaddr.sin_port));

    strcpy(buf, "Hello, client!\n");
    nbytes = strlen(buf);
    write(connfd, buf, nbytes);
    close(connfd);

    close(sockfd);

    return 0;
}
