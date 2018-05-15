#include "graphics.h"

int main(int argc, char *argv[])
{
    int fd = fb_init("/dev/fb0");
    
    fillrect(10, 10, 640, 479, 0xffffffff);
    ellipse(400, 240, 90, 140, 0xffff0000);
    line(200,200, 600, 450, 0xff0000ff);

    rectangle(300, 120, 500, 360, 0xff00ffff);
    close(fd);

	return 0;
}

