/* simplefork.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv [])
{
    int x, status ;
    pid_t pid;

    pid = fork();
    if (pid > 0) {   /* 父进程 */
        fprintf(stderr, "process ID: %d\n", getpid());
        fprintf(stderr, "child process ID: %d\n", pid);
        for(x = 1; x <= 5; x++) {
            fprintf(stderr, "%d ", x);
            sleep(1);
        }
        wait(&status);
        fprintf(stderr, "parent process ended.\n");
    } else if (pid == 0) {      /* 子进程 */
        fprintf(stderr, "parent process ID: %d\n", getppid());
        for(x = -1; x >= -5; x--) {
            fprintf(stderr, "%d ", x);
            sleep(2);
        }
        fprintf(stderr, "child process ended.\n");
        exit(0);
    } else {            /* 进程创建失败 */
        perror("fork error");
        exit(-1);
    }
    return 0;
}
