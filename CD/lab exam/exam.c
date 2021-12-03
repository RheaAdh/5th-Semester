#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char buffer[256];
char ch;
FILE *fp1;
int i = 0;
//char *lexemes[] = {""}

void success()
{
    printf("The string has been accepted!\n");
    exit(0);
}

void failure()
{
    printf("the string cant be accepted");
    exit(0);
}

void Query();
void Parameters();
void P();
void Fclause();
void Wclause();
void Exp();

int main()
{

    fp1 = fopen("input.txt", "r");
    if (fp1 == NULL)
    {
        printf("Input file cannot be opened\n");
        exit(0);
    }

    Query();

    ch = fgetc(fp1);
    if (ch == EOF)
        success();
    else
    {
        printf("main called fail\n");
        failure();
    }

    return 0;
}

void Query()
{
    i = 0;
    ch = fgetc(fp1);
    while (isalpha(ch) || isdigit(ch))
    {
        buffer[i++] = ch;
        ch = fgetc(fp1);
    }
    buffer[i] = '\0';
    if (strcmp(buffer, "select") == 0)
    {
        i = 0;
        ch = fgetc(fp1); //for the space
        while (ch == ' ')
        {
            ch = fgetc(fp1); //for any extra spaces
        }
        //rn ch has the next lexemes first letter

        Parameters();
        Fclause();
        Wclause();
    }
    else
    {
        printf("query called fail\n");
        failure();
    }
}

void Parameters()
{
    i = 0;
    while (isalpha(ch) || isdigit(ch))
    {
        buffer[i++] = ch;
        ch = fgetc(fp1);
    }
    buffer[i] = '\0';
    ch = fgetc(fp1); //for the space
    while (ch == ' ')
    {
        ch = fgetc(fp1); //for any extra spaces
    }
    if (i == 0)
    {
        //ie buffer empty so nothing will be there after ','
        printf("parameters called fail\n");
        failure();
    }
    i = 0;
    P();
}

void P()
{

    if (ch == ',')
    {
        while (isalpha(ch) || isdigit(ch))
        {
            buffer[i++] = ch;
            ch = fgetc(fp1);
        }
        buffer[i] = '\0';
        while (ch == ' ')
        {
            ch = fgetc(fp1); //for any extra spaces
        }
        Parameters();
    }
}

void Fclause()
{
    i = 0;
    while (isalpha(ch) || isdigit(ch))
    {
        buffer[i++] = ch;
        ch = fgetc(fp1);
    }
    buffer[i] = '\0';
    if (strcmp(buffer, "from") == 0)
    {
        ch = fgetc(fp1); //for the space
        while (ch == ' ')
        {
            ch = fgetc(fp1); //for any extra spaces
        }
        Parameters();
    }
    else
    {
        printf("fclause called fail\n");
        failure();
    }
}

void Wclause()
{
    i = 0;
    while (isalpha(ch) || isdigit(ch))
    {
        buffer[i++] = ch;
        ch = fgetc(fp1);
    }
    buffer[i] = '\0';
    if (strcmp(buffer, "where") == 0)
    {
        ch = fgetc(fp1); //for the space
        while (ch == ' ')
        {
            ch = fgetc(fp1); //for any extra spaces
        }
        Exp();
    }
    else
    {
        printf("wclause called fail\n");
        failure();
    }
}

void Exp()
{
    i = 0;
    while (isalpha(ch) || isdigit(ch))
    {
        buffer[i++] = ch;
        ch = fgetc(fp1);
    }
    buffer[i] = '\0';
    //have gotten id now
    ch = fgetc(fp1);
    while (ch == ' ')
    {
        ch = fgetc(fp1); //for any extra spaces
    }
    if (ch == '=')
    {
        ch = fgetc(fp1);
        while (ch == ' ')
        {
            ch = fgetc(fp1); //for any extra spaces
        }
        if (ch == '"')
        {
            ch = fgetc(fp1);
            if (isalpha(ch))
            {
                ch = fgetc(fp1);
                if (ch == '"')
                {
                    //all good
                }
                else
                {
                    printf("innermost exp called fail\n");
                    failure();
                }
            }
            else
            {
                printf("second else in exp called fail\n");
                failure();
            }
        }
        else
        {
            printf("thirs else in exp called fail\n");
            failure();
        }
    }
    else
    {
        printf("outermost exp called fail\n");
        failure();
    }
}
