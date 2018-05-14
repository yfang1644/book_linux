/* oss_record.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/soundcard.h>

#define    BUF    16
int main(int argc, char *argv[])
{
    int audio_fd;
    int mixer_fd;

    int format = AFMT_S16_NE;
    int channels = 1;
    int speed = 48000;  //44.1 KHz

    int file_fd;
    signed short applicbuf[BUF];         
    int count;

    // open device file 
    if ((audio_fd = open("/dev/dsp",O_RDWR,0)) == -1) {
        perror("/dev/dsp");
        exit(1);
    }

    /* 设置数据格式 */
    if (ioctl(audio_fd,SNDCTL_DSP_SETFMT, &format) == -1) {
        perror("SNDCTL_DSP_SETFMT");
        exit(1);
    }

    /* 设置通道数 */
    if (ioctl(audio_fd, SNDCTL_DSP_CHANNELS, &channels) == -1) {
        perror("SNDCTL_DSP_CHANNELS");
        exit(1);
    }

    /* 设置采样率 */
    if (ioctl(audio_fd, SNDCTL_DSP_SPEED, &speed) == -1) {
        perror("SNDCTL_DSP_SPEED");
        exit(1);
    } else 
        printf("Support 44.1 KHz , Actual Speed : %d \n",speed);
        
    if ((file_fd = open(argv[1], O_WRONLY | O_CREAT, 0)) == -1) {
        perror(argv[1]);
        exit(1);
    }

    /* 以下采样10秒数据，存入文件 */

    int totalbyte= speed * channels * 2 * 10; // 10 seconds
    int totalword = totalbyte/2;
    int total = 0;

    while (total != totalword) {    
        if (totalword - total >= BUF) 
            count = BUF;
        else 
            count = totalword - total;

        read(audio_fd, applicbuf, count);
        write(file_fd, applicbuf, count);
        total += count;           
    }
    close(audio_fd);
    close(file_fd);

    return 0;
}
