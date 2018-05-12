/* timer.h
 */

#ifndef _TIMER_H
#define _TIMER_H
struct dtimer {
    int port;
    char buf[1024];
} ;

#define IOCTL_MAGIC  'x'

#define TIMER_IOCRESET  _IO(IOCTL_MAGIC, 0)
/*
 * S means "Set" through a ptr
 * T means "Tell" directly with the argument value
 * G means "Get": reply by setting through a pointer
 * Q means "Query": response is on the return value
 * X means "eXchange": G and S atomically
 * H means "sHift": T and Q atomically
 *
 * BYTE: 字节读写方式 (控制寄存器 D5--D4位)
 * MODE: 计数工作方式 (控制寄存器 D3--D1位)
 */
#define TIMER_IOCSBYTE  _IOW (IOCTL_MAGIC, 1, int)
#define TIMER_IOCSMODE  _IOW (IOCTL_MAGIC, 2, int)
#define TIMER_IOCTBYTE  _IO  (IOCTL_MAGIC, 3)
#define TIMER_IOCTMODE  _IO  (IOCTL_MAGIC, 4)
#define TIMER_IOCGBYTE  _IOR (IOCTL_MAGIC, 5, int)
#define TIMER_IOCGMODE  _IOR (IOCTL_MAGIC, 6, int)
#define TIMER_IOCQBYTE  _IO  (IOCTL_MAGIC, 7)
#define TIMER_IOCQMODE  _IO  (IOCTL_MAGIC, 8)
#define TIMER_IOCXBYTE  _IOWR(IOCTL_MAGIC, 9, int)
#define TIMER_IOCXMODE  _IOWR(IOCTL_MAGIC, 10, int)
#define TIMER_IOCHBYTE  _IO  (IOCTL_MAGIC, 11)
#define TIMER_IOCHMODE  _IO  (IOCTL_MAGIC, 12)
#define TIMER_IOCHNONE  _IO  (IOCTL_MAGIC, 13) /*  debugging tool */
#define TIMER_SPEAKERON  _IO (IOCTL_MAGIC, 14)
#define TIMER_SPEAKEROFF _IO (IOCTL_MAGIC, 15)
#define TIMER_IOC_MAXNR 15

#define TIMER_HIGH     (0b00100000)  /* 计数器高字节读写 */
#define TIMER_LOW      (0b00010000)  /* 计数器低字节读写 */

#endif           /* _TIMER_H */
