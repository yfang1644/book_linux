#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main (int argc, char *argv[])
{
    time_t now;
    struct tm *t1, *t2;

    now = time(NULL);
    t1 = localtime(&now);

    sleep(3);         /* 等待3秒 */
    now += 600;       /* 计时推迟10分钟 */
    t2 = localtime(&now);

    printf("%02d:%02d:%02d in thread 1.\n",
           t1->tm_hour, t1->tm_min, t1->tm_sec);
    printf("%02d:%02d:%02d in thread 2.\n",
           t2->tm_hour, t2->tm_min, t2->tm_sec);

    return 0;
}
