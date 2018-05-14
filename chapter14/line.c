#include "graphics.h"

/* 画一条 (x0, y0) 到 (x1, y1) 的直线 */
int line(int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int sx, sy;
    int x, y, temp;
    float k;

    sx = (dx > 0)? 1: -1;
    sy = (dy > 0)? 1: -1;

    if(ABS(dx) > ABS(dy)) {     /* 缓斜线，|斜率| < 1 */
        if(x0 > x1) {
            temp = x0, x0 = x1, x1=temp;
            temp = y0, y0 = y1, y1=temp;
        }
        k = (float)dy / dx;
        for(x = x0; x <= x1; x++) {
            y = y0 + k * (x - x0);
            drawpixel(x, y, color);
        }
    } else if (ABS(dy) > ABS(dx)) {   /* 陡斜线 */
        if(y0 > y1) {
            temp = x0, x0 = x1, x1=temp;
            temp = y0, y0 = y1, y1=temp;
        }
        k = (float)dx / dy;
        for(y = y0; y <= y1; y++) {
            x = x0 + k * (y - y0);
            drawpixel(x, y, color);
        }
    } else {     /* (x0, y0) 和 (x1, y1) 重叠 */
        drawpixel(x0, y0, color);
    }
    return 0;
}
