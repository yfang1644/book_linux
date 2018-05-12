#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i = 0;

    printf("%d\n", BUFSIZ);
    for (i = 0; i < BUFSIZ*2; i++) {
        printf("A");
        usleep(4000);
    }

    return 0;
}
