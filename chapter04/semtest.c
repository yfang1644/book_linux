/* semtest.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/time.h>

static sem_t sem;

void handler(int signum)
{
    sem_post(&sem);
}

void *print(void *arg)
{
    unsigned int t;

    while (1) {
        sem_wait(&sem);
        t = *(unsigned int *) arg;
        fprintf(stderr, "%u\n", t);
    }
}

int main(int argc, char *argv [])
{
    pthread_t id;
    unsigned int i;
    struct itimerval tval;

    tval.it_interval.tv_sec = 0;
    tval.it_interval.tv_usec = 200000;
    tval.it_value = tval.it_interval;

    setitimer(ITIMER_REAL, &tval, NULL);
    signal(SIGALRM, handler);

    pthread_create(&id, NULL, print, &i);

    while (1) {
        i++;
    }

    return 0;
}
