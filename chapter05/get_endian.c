/* get_endian.c
 */

#include <stdio.h>
  
int main (int argc, char *argv[])
{   
    int i, a = 0x12345678;
    char *p = (char *)&a;
            
    for(i = 0; i < sizeof(a); i++)
        printf("%02x ", *p++);

    return 0;
}

