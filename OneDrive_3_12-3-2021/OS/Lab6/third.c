#include<stdio.h>
#include<pthread.h>
 
#define N 100
#define MX_THRDS 4
 
int prime_arr[N]={0};
 
void *displayPrime(void *ptr)
{
    int  j,flag;
    int i=(int)(long long int)ptr;
    while(i<N)
    {
        flag=0;
        for(j=2;j<=i/2;j++)
        {
            if(i%j==0)
            {
                flag=1;
                break;
            }
        }
 
        if(flag==0 && (i>1))
        {
            prime_arr[i]=1;
        }
        i+=MX_THRDS;
  }
}
 
int main()
{
    pthread_t tid[MX_THRDS]={{0}};
    int count=0;
    printf("Enter starting number and ending number\n");
    int st,en;
    scanf("%d %d",&st,&en);
 
    for(count=0;count<MX_THRDS;count++)
    {
        pthread_create(&tid[count],NULL,displayPrime,(void*)count);
    }
    printf("\n");
    for(count=0;count<MX_THRDS;count++)
    {
        pthread_join(tid[count],NULL);
    }
 
    int c=0;
    printf("Prime numbers in the specified range are:\n");
    for(count=st;count<en;count++)
        if(prime_arr[count]==1)
            printf("%d ",count);
   printf("\n");
   return 0;
}