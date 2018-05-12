/* msg.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

# define MSG_KEY    0x5678

int main(int argc, char *argv [])
{
    int msqid, ret;
    struct msgbuf {
        long mtype;
        char mtext [1024];
    } msg_buf;

    msqid = msgget(MSG_KEY, IPC_CREAT | 0600);
    if(msqid == -1 ) {
        perror("msgget error");
        exit(-1);
    }

    msg_buf.mtype = 3;
    if (!strcmp(argv[1], "send")) {
        strcpy(msg_buf.mtext, "Hello!\n");
        ret = msgsnd(msqid, &msg_buf, strlen(msg_buf.mtext), 0);
        if(ret == -1) {
            perror("msgsnd error");
            exit(-1);
        }
    } else if (!strcmp(argv[1], "read")) {
        ret = msgrcv (msqid, &msg_buf, 1024, msg_buf.mtype, 0);
        if (ret == -1) {
            perror("msgrcv error");
            exit(-1);
        }
        fprintf(stderr, "Messge received : %s", msg_buf.mtext);
    }

    return 0;
}
