/* talkc_2.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

int main(int argc, char *argv[])
{
    int sockfd, port, keychars, sockchars, retval;
    char buf1[1024], buf2[1024];
    struct sockaddr_in srvaddr;
    fd_set rfds, wfds;
    struct timeval tv;

    if(argc != 3){
        printf("usage: %s hostname port", argv[0]);
        return -1;
    }

    port = atoi(argv[2]);
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("create socket error.");
        return -2;
    }
    bzero(&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(port);
    srvaddr.sin_addr.s_addr = inet_addr(argv[1]);
    if(connect(sockfd, (struct sockaddr *)&srvaddr,
            sizeof(struct sockaddr)) == -1){
                perror("conenct error.");
                return -3;
    }

    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    while(1) {
        FD_SET(sockfd, &rfds);
        FD_SET(STDIN_FILENO, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 100000;         /*  Wait up to 100ms. */
        retval = select(sockfd + 1, &rfds, &wfds, NULL, &tv);

        if (FD_ISSET(STDIN_FILENO, &rfds)) {
            keychars = read(STDIN_FILENO, buf1, 1024);
            write(sockfd, buf1, keychars);
        }

        if (FD_ISSET(sockfd, &rfds)) {
            sockchars = read(sockfd, buf2, 1024);
            write(STDOUT_FILENO, buf2, sockchars);
        }
    }
    close(sockfd);

    return 0;
}
