/* apps.c
 */

/*
* timer 驱动测试程序。
* 创建设备文件 /dev/timer:
*     mknod /dev/timer c 123 2 -m 666
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "timer.h"

int main (int argc, char *argv[])
{
    int i, cnt; 
    int notes [] = {        /* 音阶频率表 */
        131, 147, 165, 175, 196, 220, 247, 262
    };
    int fd = open("/dev/timer", O_RDWR);

    if(fd < 0) {
        perror("Open /dev/timer error.");
        return -1;
    }
    ioctl(fd, TIMER_IOCSMODE, 3 << 1);      /* 方波方式 */
    ioctl(fd, TIMER_IOCSBYTE, 0b00110000);  /* 高低8位操作 */

    ioctl(fd, TIMER_SPEAKERON, 0);
    for(i = 0; i < 8; i++) {
        cnt = 1193182 / notes [i];
        write(fd, &cnt, 2);
        usleep(200000);
    }
    ioctl(fd, TIMER_SPEAKEROFF, 0);
    close(fd);

    return 0;
}
