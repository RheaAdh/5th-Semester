#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc, char *argv[])
{
    int in,out;

    if(argc!=2)
    {
        printf("Insufficient Arguments\n");
        exit(1);
    }

    in=open(argv[1],O_RDWR);
    out=open(argv[1],O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

    if(out==-1)
    {
        printf("File not found\n");
        exit(1);
    }
    else{
        printf("---------Opened file--------\n");
    }

     int sum=0;
     int n;

     printf("Enter n: \n");
     scanf("%d",&n);

     
     printf("Forking...\n");
     
     int id;
     id=fork();

     if(id==-1){
        printf("Issue in Fork");
        exit(0);
     }

     if(id==0){
        printf("Entered Child Process!\n");

        for(int i=1;i<=n;i++){
            sum+=i;
            if(i==n)
            printf("sum=%d\n",sum);
        }
        // write to file
        write(out,sum,1);
        printf("Wrote to file = %d\n",write(out,sum,1));
     }
     else{
        sleep(5);
        int num;
        printf("Entered Parent Process!\n");

        int ans=read(in,&num,1);
        printf("Read from file = %d\n",read(in,&num,1));
        printf("sum=%d\n",ans);
     }
     return 0;
     
}