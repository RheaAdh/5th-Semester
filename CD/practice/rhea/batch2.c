#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

FILE *fp;
int i = 0;
char c;
char buffer[100];

void valid()
{
    printf("valid!\n");
    exit(0);
}

void invalid(int x)
{
    printf("invalid = %d\n", x);
    printf("stops before this:\n");
    while (c != EOF)
    {
        printf("curr char = %c\n", c);
        c = fgetc(fp);
    }
    exit(0);
}

void Query()
{
    printf("query\n");
    i = 0;
    c = fgetc(fp);
    while (isalpha(c))
    {
        buffer[i++] = c;
        c = fgetc(fp);
    }
    buffer[i] = '\0';
    if (strcmp(buffer, "select") == 0)
    {
        while (c == ' ')
        {
            c = fgetc(fp);
        }
        // has next character
        Parameters();
        Fclause();
        Wclause();
    }
    else
    {

        invalid(1);
    }
}

void Parameters()
{
    // id
    printf("Parameters\n");
    while (isalnum(c))
    {
        c = fgetc(fp);
    }
    // encouter space
    while (c == ' ')
    {
        c = fgetc(fp);
    }
    // has next char
    ParametersPrime();
}

void ParametersPrime()
{
    printf("ParametersPrime\n");
    if (c == ',')
    {
        printf(",\n");
        c = fgetc(fp);
        while (c == ' ')
        {
            c = fgetc(fp);
        }
        // has next char
        Parameters();
    }
}

void Fclause()
{
    printf("Fclause\n");
    i = 0;
    while (isalpha(c))
    {
        buffer[i++] = c;
        c = fgetc(fp);
    }
    // encounter space
    buffer[i] = '\0';
    if (strcmp(buffer, "from") == 0)
    {
        while (c == ' ')
        {
            c = fgetc(fp);
        }
        // has next char
        Parameters();
    }
    else
    {
        invalid(2);
    }
}

void Wclause()
{
    printf("Wclause\n");
    i = 0;
    while (isalpha(c))
    {
        buffer[i++] = c;
        c = fgetc(fp);
    }
    // encounter space
    buffer[i] = '\0';
    if (strcmp(buffer, "where") == 0)
    {
        while (c == ' ')
        {
            c = fgetc(fp);
        }
        // has next char
        Expression();
    }
    else
    {
        invalid(3);
    }
}
void Expression()
{
    printf("exp\n");
    i = 0;
    while (isalnum(c))
    {
        buffer[i++] = c;
        c = fgetc(fp);
    }
    // encounter space
    buffer[i] = '\0';
    while (c == ' ')
    {
        c = fgetc(fp);
    }
    // has next char
    if (c == '=')
    {
        c = fgetc(fp);
        // encounter space
        while (c == ' ')
        {
            c = fgetc(fp);
        }
        // has next character
        if (c == '"')
        {
            c = fgetc(fp);
            // encounter character
            while (isalnum(c))
            {
                c = fgetc(fp);
            }
            if (c == '"')
            {
                // GG
            }
            else
            {
                invalid(4);
            }
        }
        else
        {
            invalid(5);
        }
    }
    else
    {
        invalid(6);
    }
}
int main()
{
    fp = fopen("batch2.txt", "r");
    if (fp == NULL)
    {
        printf("Cant open input file");
        exit(0);
    }
    else
    {
        printf("Input file opening....\n");
    }

    Query();

    c = fgetc(fp);

    if (c == EOF)
    {
        valid();
    }
    else
    {
        invalid(7);
    }
}