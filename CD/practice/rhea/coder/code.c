#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "la.h"
#include <string.h>

FILE *fp1;
Token tok;
int unget = 0, flag = 0;

void query();
void parameters();
void parametersPrime();
void flcause();
void wclause();
void exp();
void invalid()
{
    printf("invalid\n");
    exit(0);
}
void valid()
{
    printf("valid\n");
    exit(0);
}
void checkAndGet()
{
    if (!unget) //unget=0 so !0=1
    {
        tok = getNextToken(fp1);
    }
    else
    {
        unget = 0;
    }
}
void query()
{
    checkAndGet();
    if (strcmp("select", tok.lexeme) == 0)
    {
        parameters();
        fclause();
        wclause();
    }
    else
    {
        invalid();
        flag = 1;
    }
}

void parameters()
{
    checkAndGet();
    if (strcmp(tok.type, "id") == 0)
    {
        parametersPrime();
    }
    else
    {
        invalid();
        flag = 1;
    }
}

void parametersPrime()
{
    checkAndGet();
    if (strcmp(tok.lexeme, ',') == 0)
    {
        parameters();
    }
    else
    {
        unget = 1;
    }
}

void fclause()
{
    checkAndGet();
    if (strcmp(tok.type, "from") == 0)
    {
        parameters();
    }
    else
    {
        invalid();
        flag = 1
    }
}
void wclause()
{
    checkAndGet();
    if (strcmp("where", tok.type) == 0)
    {
        exp();
    }
    else
    {
        invalid();
        flag = 1;
    }
}

void exp()
{
    checkAndGet();
    if (strcmp("id", tok.type) == 0)
    {
        checkAndGet();
        if (strcmp("=", tok.lexeme) == 0)
        {
            checkAndGet();
            if (strcmp("\'", tok.lexeme))
            {
                checkAndGet();
                if (isalpha(tok.lexeme[0]))
                {
                    checkAndGet();
                    if (strcmp("\'", tok.lexeme))
                    {
                        valid();
                    }
                    else
                    {
                        invalid();
                        flag = 1;
                    }
                }
                else
                {
                    invalid();
                    flag = 1;
                }
            }
            else
            {
                invalid();
                flag = 1;
            }
        }
        else
        {
            invalid();
            flag = 1;
        }
    }
    else
    {
        invalid();
        flag = 1;
    }
}
int main()
{
    fp1 = fopen("input.sql", "r");
    if (fp1 == NULL)
    {
        printf("cant open file");
        exit(0);
    }
    printf("Opened file!\n");

    query();

    fclose(fp1);

    return 0;
}