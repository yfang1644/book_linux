/* tcp_client.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv [])
{
    int sockfd, nbytes, port;
    char buf[1024];
    struct sockaddr_in srvaddr ;

    if(argc != 3){
        printf("usage : %s hostname port", argv[0]);
        return -1;
    }

    port = atoi(argv [2]);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("create socket error.");
        return -2;
    }

    bzero(&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons (port);
    srvaddr.sin_addr.s_addr = inet_addr(argv[1]);
    if(connect(sockfd, (struct sockaddr *)&srvaddr ,
               sizeof(struct sockaddr)) == -1){
                   perror("conenct error.");
                   return -3;
               }
    if ((nbytes = read(sockfd, buf, 1024)) == -1) {
        perror("read error.");
        return -4;
    }
    write(STDOUT_FILENO, buf, nbytes);
    close(sockfd);

    return 0;
}
