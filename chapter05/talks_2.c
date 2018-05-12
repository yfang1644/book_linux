/* talks_2.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>

#define SERV_PORT   5678

int main(int argc, char *argv[])
{
    int sockfd, connfd, addrlen, keychars, sockchars, retval, maxfd;
    char buf1[1024], buf2[1024];
    struct sockaddr_in srvaddr, cliaddr;
    fd_set rfds, wfds;
    struct timeval tv;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
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
    if(listen(sockfd, 5) == -1) {
        perror("listen error.");
        return -3;
    }

    connfd = accept(sockfd, (struct sockaddr *)&cliaddr,
                       &addrlen);
    maxfd = (connfd > sockfd) ? connfd : sockfd;
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    while(1) {
        FD_SET(connfd, &rfds);
        FD_SET(STDIN_FILENO, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 100000;         /*  Wait up to 100ms. */
        retval = select(maxfd + 1, &rfds, &wfds, NULL, &tv);

        if (FD_ISSET(STDIN_FILENO, &rfds)) {
            keychars = read(STDIN_FILENO, buf1, 1024);
            write(connfd, buf1, keychars);
        }
        if (FD_ISSET(connfd, &rfds)) {
            sockchars = read(connfd, buf2, 1024);
            write(STDOUT_FILENO, buf2, sockchars);
        }
    }
    close(connfd);
    close(sockfd);

    return 0;
}
