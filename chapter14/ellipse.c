#include <math.h>
#include "graphics.h"

int ellipse(int x0, int y0, int a, int b, int color)
{
    int x, y;
    float theta, dth;
    int axis_m;
    
    axis_m = (a > b) ? a : b;
    if (axis_m <= 0)
        return -1;
    dth = 1.57/axis_m;

    for(theta = 0.0; theta <= M_PI/2; theta += dth) {
        x = a * cos(theta);
        y = b * sin(theta);
        drawpixel(x0 + x, y0 + y, color);
        drawpixel(x0 - x, y0 + y, color);
        drawpixel(x0 + x, y0 - y, color);
        drawpixel(x0 - x, y0 - y, color);
    }

    return 0;
}
