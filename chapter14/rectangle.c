/*
 * ============================================================================
 *
 *       Filename:  rectangle.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/11/2018 08:41:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Yuan (yfang@nju.edu.cn)
 *   Organization:  nju
 *
 * ============================================================================
 */

#include "graphics.h"
/* 两个顶点 (x0, y0) -- (x1, y1) 决定的矩形 */
int rectangle(int x0, int y0, int x1, int y1, int color)
{
    int ret = 0;

    ret += line(x0, y0, x1, y0, color);
    ret += line(x1, y0, x1, y1, color);
    ret += line(x1, y1, x0, y1, color);
    ret += line(x0, y1, x0, y0, color);

    return ret;
}

/* 填充矩形 */
int fillrect(int x0, int y0, int x1, int y1, int color)
{
    int x, y, temp;

    if (x0 > x1) {
        temp = x0, x0 = x1, x1 = temp;
    }
    if (y0 > y1) {
        temp = y0, y0 = y1, y1 = temp;
    }
    for(y = y0; y <= y1; y++) {
        for(x = x0; x <= x1; x++) {
            drawpixel(x, y, color);
        }
    }
    return 0;
}
