/* thread.c
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

static pthread_mutex_t mutex;

void *timer1(void *arg)
{
    int t = *(int *)arg;
    pthread_mutex_unlock(&mutex);

    do {
        fprintf (stderr, "%d ",t--);
        sleep(1);
    } while (t >= 0);
}

void *timer2(void *arg)
{
    int t = *(int *)arg;
    pthread_mutex_unlock(&mutex);

    while (1) {
        fprintf(stderr, "%d\n", t++);
        sleep(1);
    }
}

int main(int argc, char *argv [])
{
    pthread_t id;
    int i;

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);
    i = 10;
    pthread_create(&id, NULL, timer1, &i);

    pthread_mutex_lock(&mutex);
    i = 0;
    pthread_create(&id, NULL, timer2, &i);
    sleep(20);

    return 0;
}

