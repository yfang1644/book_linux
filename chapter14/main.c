#include "graphics.h"

int main(int argc, char *argv[])
{
    fb_init("/dev/fb0");
    
    fillrect(0,0, 799, 479, 0xffffffff);
    ellipse(400, 240, 90, 140, 0xffff0000);

    rectangle(300, 120, 500, 360, 0xff00ffff);

	return 0;
}

