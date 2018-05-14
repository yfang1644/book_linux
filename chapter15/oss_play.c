/* oss_play.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/soundcard.h>

#define	BUF	40

int main(int argc, char *argv[])
{
    int audio_fd;
    int format = AFMT_S16_NE;
    int channels = 1;    /* 单声道 */
    int speed = 16000;   /* 采样率*/
    int file_fd;
    signed short applicbuf[BUF];         
    int count;

    // open device file 
    if ((audio_fd = open("/dev/dsp",O_RDWR,0)) == -1) {
        perror("/dev/dsp");
        exit(1);
    }

    /*  设置数据格式 */
    if (ioctl(audio_fd,SNDCTL_DSP_SETFMT, &format) == -1) {
        perror("SNDCTL_DSP_SETFMT");
        exit(1);
    }
    /* 设置通道数 */
    if (ioctl(audio_fd, SNDCTL_DSP_CHANNELS, & channels) == -1) {
        perror("SNDCTL_DSP_CHANNELS");
        exit(1);
    }

    /* 设置采样率 */
    if (ioctl(audio_fd, SNDCTL_DSP_SPEED, &speed) == -1) {
        perror("SNDCTL_DSP_SPEED");
        exit(1);
    } else 
        printf("Actual Speed : %d \n",speed);

    if ((file_fd = open(argv[1], O_RDONLY, 0)) == -1) {
        perror(argv[1]);
        exit(1);
    }

    /* 读取数据文件，写入声卡 */
    while ((count = read(file_fd, applicbuf, BUF)) > 0) {
        write(audio_fd, applicbuf, count);
    }

    close(audio_fd);
    close(file_fd);

    return 0;
}
