/* zombie.c
 */

#include <sys/wait.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        _exit(0); 
    } else {
        sleep(20);
        waitpid(pid, NULL, 0);
    }

    return 0;
}
