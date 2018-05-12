/* redir.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv [])
{
    int fd;

    fd = open("/var/log/error.log", O_RDWR |O_CREAT, 0644);
    if (fd < 0) {
        perror("file open error.\n");
        exit(-1);
    }

    dup2(fd, STDERR_FILENO);
    fprintf(stderr, "This is an error message.\n");

    return 0;
}
