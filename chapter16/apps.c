/* apps.c
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "gpio.h"

int main(int argc, char *argv[])
{
    int fd;
    int val, i;

    fd = open(argv[1], O_RDWR);

	ioctl(fd, LEDIOGET, &val);
    val &= ~(0b11 << 12);         /* GPIO12、GPIO13 设为输出 */
	ioctl(fd, LEDIOSET, &val);
    for(i = 0; i < 10; i++) {
		val = (0b11 << 12);
		write(fd, &val, 4);
		usleep(200000);
		val = (0b00 << 12);
		write(fd, &val, 4);
		usleep(200000);
	}

	ioctl(fd, LEDIOGET, &val);
	val |= (0b11 << 12);          /* GPIO12、GPIO13 设为输入 */
	ioctl(fd, LEDIOSET, &val);
	for(;;) {
		read(fd, &val, 4);
		printf("%X\n", val);
		usleep(200000);
	}
    close(fd);

    return 0;
}
