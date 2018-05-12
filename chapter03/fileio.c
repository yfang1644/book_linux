/* fileio.c
 */

#include <unistd.h>
#include <fcntl.h>

# define BUFFSIZE 4096
int main (int argc, char *argv [])
{
    char buf[BUFFSIZE];
    int n;
    
    while (1) {
        n = read(STDIN_FILENO, buf, BUFFSIZE);
        if (n > 0)
            write(STDOUT_FILENO, buf, n);
        else
            break;
    }

    return 0;
}
