/* shmem.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/shm.h>

int main(int argc, char *argv [])
{
    int shmid, status;
    char *shmaddr ;
    pid_t pid;

    shmid = shmget(IPC_PRIVATE, 4096, IPC_CREAT | 0600);
    if( shmid < 0 ) {
        perror("shmget error");
        exit(-1);
    }
    shmaddr = (char *)shmat(shmid, NULL, 0);
    if(shmaddr == (void *)-1) {
        perror("shmat error in child process");
        exit(-1);
    }

    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(-1);
    }

    if(pid > 0) {           /* 父进程 */
        strcpy(shmaddr, "Hello!\n");
        wait(&status);
        shmdt(shmaddr);
        shmctl(shmid, IPC_RMID, NULL);
        return 0;
    }
    if(pid == 0) {          /* 子进程 */
        sleep(1);
        fprintf(stderr, "get msg from parent : %s\n", shmaddr);
        exit(0);
    }
}
