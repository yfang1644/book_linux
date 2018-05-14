#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <linux/fb.h>

static struct fb_fix_screeninfo finfo;
static struct fb_var_screeninfo vinfo;
static unsigned char *fbmem;

/* 在 (x, y) 处画一个颜色为color 的点.
   本程序只适用于RGBA 32位 Frame buffer 格式. */
int drawpixel(int x, int y, int color)
{
    unsigned int ptr;

    if((x >= vinfo.xres) || (x < 0)
       || (y >= vinfo.yres) || (y < 0))
        return -1;
    ptr = y * finfo.line_length + x * 4;
    *(unsigned int *)(fbmem + ptr) = color;

    return 0;
}

/* 初始化 Frame Buffer，获得缓冲区首地址 fbmem */
int fb_init(char *dev)
{
    int fd;
    long screensize = 0;

    fd = open(dev, O_RDWR);

    if (fd < 0){
        printf("Error : Can not open framebuffer device\n");
        exit(-1);
    }
    ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
    ioctl(fd, FBIOGET_FSCREENINFO, &finfo);
    printf("Resolution: x = %d, y = %d\n", vinfo.xres, vinfo.yres);

    screensize = vinfo.xres*vinfo.yres*(vinfo.bits_per_pixel/8);
    fbmem = (char *)mmap(0, screensize, PROT_READ|PROT_WRITE,
                         MAP_SHARED, fd,0);
    if (fbmem == NULL) {
        printf ("Error: failed to map framebuffer device to memory.\n");
        exit(-1);
    }

    return fd;
}
