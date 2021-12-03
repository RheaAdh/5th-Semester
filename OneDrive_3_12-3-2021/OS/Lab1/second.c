#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc, char *argv[])
{
 
    int FD1,FD2,i=0,k=0,p=0;
    char ch[100],ch2[100],chr;
 
    if(argc!=3)
    {
        printf("Insufficient Arguments\n");
        exit(1);
    }
 
    if( (FD1=open(argv[1],O_RDONLY))==-1)
    {
        printf("File not found\n");
        exit(1);
    }
 
  
    while((read(FD1,&chr,1))>0)
    { 
        if(chr!='\n')
        {
            ch[i]=chr;
            i++;
        }
 
        else
        {
            k++;
            p++;
            ch[i]='\0';
            i=0;
            printf("Line:%d \t %s \n", p,ch);
            if(k==20)
            {
                fgetc(stdin);
                k=0;
            }
        }
    }
    close(FD1);
 
    if( (FD2=open(argv[2],O_RDONLY))==-1)
    {
        printf("File not found\n");
        exit(1);
    }
 
    p=0;
 
    while((read(FD1,&chr,1))>0)
    {
        if(chr!='\n')
        {
            ch2[i]=chr;
            i++;
        }
 
        else
        {
            k++;
            p++;
            ch[i]='\0';
            i=0;
            printf("Line:%d \t %s \n", p,ch2);
            if(k==20)
            {
                fgetc(stdin);
                k=0;
            }
        }
    }
    exit(0);
}
