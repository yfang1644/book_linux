/* bufferio.c
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv [])
{
    for (int i = 0; i < 10; i++) {
        printf("%d ", i);
        sleep(1);
    }

    return 0;
}
