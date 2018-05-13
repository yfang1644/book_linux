/* notes.c
 */

#include <sys/io.h>
#include <unistd.h>

int main(int argc, char *argv [])
{
    int notes [] = {        /* 音阶频率表 */
        131, 147, 165, 175, 196, 220, 247, 262
    };
    int i, cnt;
    unsigned char hi, lo;

    /*  setuid(getuid()); */
    ioperm (0x42, 0x2, 0xffff );
    ioperm (0x61, 1, 0xffff );
    outb(0xb6, 0x43);       /* 设置方波输出 */
    outb(0x3, 0x61);        /* 打开扬声器开关 */

    for(i = 0; i < 8; i++) {
        cnt = 1193182 / notes [i];
        hi = cnt / 256;
        lo = cnt % 256;     /* 跟据频率计算计数值 */
        outb(lo, 0x42);
        outb(hi, 0x42);     /* 高低字节分两次写入 */
        usleep(200000);
    }
    outb (0, 0x61);         /* 关闭扬声器开关 */

    return 0;
}

