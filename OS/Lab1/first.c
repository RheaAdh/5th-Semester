#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc, char *argv[])
{
 
    int FD;
    int i=0;
    int lines=0;
    char ch[100];
    char chr;
 
    if(argc<2)
    {
        printf("Insufficient Arguments\n");
        exit(1);
    }
 
    if( (FD=open(argv[1],O_RDONLY))==-1)
    {
        printf("File not found\n");
        exit(1);
    }
 
   
    while((read(FD,&chr,1))>0)
    {
        if(chr!='\n')
        {
            ch[i]=chr;
            i++;
        }
 
        else
        {
            lines++;
            ch[i]='\0';
            i=0;
            printf("Line:%d \t %s \n",lines,ch);
            
        }
    }
    printf("Total no.of lines = %d\n",lines);
    exit(0);
 
}


