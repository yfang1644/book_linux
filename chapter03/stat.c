#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct stat buf;
    int ret;

    if(argc < 2) {
        printf("An exist filename is needed.\n");
        return -1;
    }
    ret = stat(argv[1], &buf);
    if (ret < 0) {
        printf("File open error.\n");
        return -1;
    }
    printf("%ld\n", buf.st_size);
    printf("%.24s\n", ctime(&buf.st_atim.tv_sec));

    return 0;
}
