#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
    int fd_serv, fd_cli, n;
    int pid, ret;
    char str[256];

    fd_serv = open("/tmp/serv", O_RDWR);
    pid = getpid();
    sprintf(str, "/tmp/%d", pid);
    n = strlen(str);
    write(fd_serv, str, n);

    do {              /* 等待服务器创建管道 */
        fd_cli = open(str, O_RDWR);
    } while (fd_cli < 0);

    while(1) {
        n = read(fd_cli, str, 255);
        write(STDOUT_FILENO, str, n);
        n = read(STDIN_FILENO, str, 255);
        write(fd_serv, str, n);
    }

    return 0;
}
