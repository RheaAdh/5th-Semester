#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/msg.h>

struct myMessage
{
    long int my_msg_type;
    int msg;
};

int reverse(int x)
{
    return x - 1;
}

int main()
{
    int runing = 1;
    struct myMessage some_data;
    long int msg_to_receive = 0;
    int msgid;
    int num;
    msgid = mssget((key_t)1234, 066 | IPC_CREAT);
    if (msgid == -1)
    {
        fprintf(stderr, "msg faile with err");
        exit(EXIT_FAILURE);
    }

    while(running P_ALLif(msgrcv(msgid,(void *))))
}