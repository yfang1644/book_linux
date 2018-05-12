/* guests.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define SERV_PORT   9999

int main(int argc, char *argv[])
{
    int sockfd, connfd, addrlen, n;
    char buf[1024];
    struct sockaddr_in srvaddr, cliaddr;
    pid_t pid;
    int pipefd[2];

    int counter = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(SERV_PORT);
    srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    addrlen = sizeof(struct sockaddr);

    bind(sockfd, (struct sockaddr *)&srvaddr, addrlen);

    listen(sockfd, 5);

    /* 取消下面函数调用的注释，程序将以守护进程方式运行 */
    //   daemon(0, 0);

    while(1) {
        connfd = accept(sockfd, (struct sockaddr *)&cliaddr,
                        &addrlen);
        pipe(pipefd);  
        pid = fork();
        if(pid == 0) {
            close(pipefd[1]);
            read(pipefd[0], &counter, 4);
            close(pipefd[0]);
            n = sprintf(buf, "Total visited guests: %d\n", counter);
            write(connfd, buf, n);
            close(connfd);
            exit(0);
        } else {
            close(pipefd[0]);
            counter++;
            write(pipefd[1], &counter, 4);
            close(pipefd[1]);
            close(connfd);
        }
    }

    close(sockfd);

    return 0;
}
