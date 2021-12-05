#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
FILE *fp;
char c;
int i = 0;
char buffer[100];
void valid()
{
    printf("valid\n");
    exit(0);
}
void invalid()
{
    printf("invalid\n");
    exit(0);
}
void query()
{
    i = 0;
    c = fgetc(fp);
    while (isalpha(c))
    {
        buffer[i++] = c;
        c = fgetc(fp);
    }
    // c is at a space
    buffer[i] = '\0';
    if (strcmp(buffer, "select") == 0)
    {
        while (c != ' ')
        {
            c = fgetc(fp);
        }
        // has next char
        Parameters();
        Fclause();
        Wclause();
    }
    else
    {
        invalid();
    }
}
void Parameters()
{
    i = 0;
    while (isalpha(c))
    {
        c = fgetc(fp);
    }
    // next char
    ParametersPrime();
}
void ParametersPrime()
{
    if (c =)
}
int main()
{
    fp = fopen("batch2.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening input file\n");
        exit(0);
    }
    else
    {
        printf("opened file....\n");
    }
    query();
    c = fgetc(fp);
    if (c == EOF)
    {
        invalid();
    }
    else
    {
        valid();
    }
}