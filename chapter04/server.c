#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    int fd_serv, fd_cli, n;
    int pid, ret;
    char str[256];

    fd_serv = open("/tmp/serv", O_RDONLY); /* 打开公共管道 */

    n = read(fd_serv, str, 1024);     /* 接收客户端传来的信息 */
    str[n] = '\0';
    mkfifo(str, 0666);              /* 创建通信管道 */
    fd_cli = open(str, O_RDWR);

    while(1) {
        n = read(STDIN_FILENO, str, 255);
        write(fd_cli, str, n);      /* 从标准输入设备读，写入管道 */
        n = read(fd_serv, str, 255);
        write(STDOUT_FILENO, str, n); /* 从管道读取，写到终端上 */
    }
    return 0;
}
