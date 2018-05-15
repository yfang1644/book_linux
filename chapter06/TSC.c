/* TSC.c
 */

#include <stdio.h>
#define rdtsc(low ,high) \
    __asm__ __volatile__ (" rdtsc " : "=a" (low), "=d" (high ))
  
#define CLK  2294720000  /*  2.294GHz */
      
int main(int argc, char *argv[])
{
    unsigned long l1, h1, l2, h2;
    unsigned long long t1, t2;
                
    rdtsc(l1, h1);
    printf("%ld %ld\n", h1, l1);
    t1 = h1*(1L<<32) + l1;
    while(1) {
        rdtsc(l2, h2);
        t2 = h2*(1L<<32) + l2;
        if (t2 - t1 > CLK*3600)
            break;
    }
    printf("%ld %ld\n", h2, l2);

    return 0;
}
