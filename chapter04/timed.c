/* timed.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>

void daemon_init(const char *pname, int facility)
{
    int i;
    int maxfd;
    
    if(fork() != 0)
        exit(0);                /* 父进程退出 */
    if(setsid() < 0)
        exit(0);                /* 设置会话组头 */
    signal(SIGHUP, SIG_IGN);    /* 忽略信号 SIGHUP */

    if(fork() != 0)
        exit(0);                /* 再次退出父进程 */

    chdir("/");                 /* 切换目录，与文件系统脱钩 */
    umask(0);
    maxfd = sysconf(_SC_OPEN_MAX);
    for(i = 0; i < maxfd; i++)
        close(i);               /* 关闭所有文件 */
    openlog(pname, LOG_PID, facility );
}

int main(int argc, char *argv [])
{
    int fd;
    time_t ticks;
    char buf[128];

    daemon_init(argv[0], 0);

    fd = open("/tmp/timer.log", O_WRONLY | O_CREAT |O_APPEND, 0644);
    while(1) {
        if (fd == -1) {
            perror("open error");
            exit(-1);
        }
        ticks = time(NULL);
        snprintf(buf, sizeof(buf), "%.24s\n", ctime (&ticks));
        write(fd, buf, strlen(buf));
        fsync(fd);

        sleep(60);
    }
    close(fd);
}
