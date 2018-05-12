/* pipe.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv [])
{
    int status, pipefd[2], n;
    char buf[1024];
    pid_t pid;

    if (pipe(pipefd) < 0) {
        perror("pipe error");
        exit(-1);
    }

    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(-1);
    }

    if (pid > 0) {          /* 父进程 */
        close(pipefd[0]);   /* 关闭读端口 */
        write(pipefd[1], "Hello!\n", 7);
        wait(&status);
        return 0;
    }

    if (pid == 0) {         /* 子进程 */
        close(pipefd[1]);   /* 关闭写端口 */
        n = read(pipefd[0], buf, 1024);
        write(STDERR_FILENO, buf, n);
        exit(0);
    }
}
