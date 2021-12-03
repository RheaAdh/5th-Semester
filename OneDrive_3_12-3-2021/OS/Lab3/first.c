#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
 
int main(int argc, char const *argv[])
{
    int st;
    pid_t pid;

    // Fork parent process
    pid = fork();
 
    if(pid == -1)
    {
        printf("Error creating child process\n");
    }
    else if(pid == 0)
    {
        printf("I'm the child process\n");
        exit(0);
    }
    else 
    {
        wait(&st);
        printf("I'm the parent process\n");
        printf("Child returned status : %d\n",st);
    }
    return 0;
}