#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#define  ABS(x)    (((x)>=0)? (x): -(x))

int fb_init(char *dev);
int drawpixel(int x, int y, int color);

int line(int x0, int y0, int x1, int y1, int color);
int ellipse(int x0, int y0, int a, int b, int color);

int rectangle(int x0, int y0, int x1, int y1, int color);
int fillrect(int x0, int y0, int x1, int y1, int color);

#endif    /* _GRAPHICS_H */
