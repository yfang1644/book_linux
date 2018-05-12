/* structsize.c
 */

#include <stdio.h>
  
int main (int argc, char *argv[])
{
    struct tagBitmapFileHeader {
        unsigned short bmp_Type;
        unsigned long bmp_Size;
        unsigned short bmp_Reserved1;
        unsigned short bmp_Reserved2;
        unsigned long bmp_OffBits ;
    };

    printf("%d\n", sizeof(struct tagBitmapFileHeader));

    return 0; 
}
