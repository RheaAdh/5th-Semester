#include<stdio.h>
#include<stdlib.h>
 
int main()
{
 
    FILE* fptr;
    int num=0;
    fptr=fopen("demo.bin","wb+");
 
    printf("Enter few numbers : \n");
 
    for(int i=0;i<4;i++)
    {
 
        scanf("%d",&num);
        fwrite(&num,sizeof(int),1,fptr);
    }
 
    printf("Writing operation over.\n");
    fclose(fptr);
 
    fptr=fopen("demo.bin","rb");
 
    for(int i=0;i<4;i++)
    {
 
        fread(&num,sizeof(int),1,fptr);
        printf("%d\n",num);
    }
 
}