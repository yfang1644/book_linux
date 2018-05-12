#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = SIG_IGN;
    sigaction (SIGTERM, &sa, NULL);
    while(1) {
        fprintf(stderr,".");
        sleep(1);
    }

    return 0;
}
