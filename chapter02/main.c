/* main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "prime.h"

int main (int argc, char *argv [])
{
    struct timeval t_begin, t_end ;
    int val, maxv;
    int res;

    maxv = atoi(argv[1]);     /* 最大值由命令参数给出 */
    gettimeofday(&t_begin, NULL);

    for (val = 2; val < maxv; val ++) {
        res = prime(val);
        if(res)
            printf("%d is a prime.\n", val);
        else
            printf("%d is not a prime.\n", val);
    }
    gettimeofday(&t_end, NULL);
    printf ("total time: %ld(us).\n",
            (t_end.tv_sec - t_begin.tv_sec)*1000000
            + (t_end.tv_usec - t_begin.tv_usec));
    return 0;
}
