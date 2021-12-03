#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>



#define handle_error_en(en, msg)



/*do
{
errno = en;
perror(msg);
exit(0);}while(0)*/



volatile int running_threads = 0;



pthread_t thread[1];



int numOfElements;



struct Results
{
int sum;
}Results,Results2;



void *findsum(void *array_ptr)
{
int i; /*counter*/
int *elements=(int*)array_ptr;



for(i=0;i<numOfElements;i++)
{
if(elements[i]%2==0)
Results.sum+=elements[i];
else
Results2.sum+=elements[i];
}
running_threads -= 1;
return NULL;
}



int getArrayInput(int n,int *array_ptr)
{
int input;
int numberOfElements = 0;
printf("Creating a dynamic array\n\n");
for(;;)
{
printf("Enter a +ve integer OR -ve integer to stop\n\n");
if (scanf("%d",&input)!= 1)
{
printf("Not an integer\n");
exit(0);
}
if (input>=0)
{
if (numberOfElements==n)
{
n+=1;
array_ptr = realloc(array_ptr, n * sizeof(int));
}
array_ptr[numberOfElements++]=input;
}
else
{
printf("\nNumber of Integers: %d\n", numberOfElements);
break;
}
}
return numberOfElements;
}



void createThreads(int *array_ptr)
{
int s;
s = pthread_create(&thread[2], NULL, findsum, (void *)array_ptr);
if (s != 0)
handle_error_en(s, "pthread_create");
running_threads += 1;
}



int main()
{
int n = 1;
int *array_ptr = malloc(n*sizeof(int));
numOfElements = getArrayInput(n, array_ptr);
createThreads(array_ptr);
while(running_threads>0)
sleep(1);
printf("\nThe sum of even numbers= %d\n",Results.sum);
printf("\nThe sum of odd numbers= %d\n",Results2.sum);
return(0);
}