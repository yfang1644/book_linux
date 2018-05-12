/* puts.c
 */

#include <stdio.h>     /* include puts() */
#include <stdlib.h>
#include <unistd.h>

/* 重写的 puts() */
int puts_STDOUT(const char *s)
{
    char *p = (char *)s;
    char r = '\n';
    int len = 0, ret;

    while(1) {
        if (*p++ == '\0')
            break;
        len++;
    }
    ret = write(STDOUT_FILENO, s, len);
    if (ret != len)
        return ret;
    ret = write(STDOUT_FILENO, &r, 1);
    if (ret != 1)
        return ret;
    else
        return len + 1;
}

/* 对比测试程序 */
int main(int argc, char *argv[])
{
    puts("This is a test line.\n Hello, world.");
    puts_STDOUT("This is a test line.\n Hello, world.");

    return 0;
}
