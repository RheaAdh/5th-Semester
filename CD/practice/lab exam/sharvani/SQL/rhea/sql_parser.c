#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "sql_la.c"

FILE *fp;
struct TOKEN tok;
int flag = 0;
int unget = 0;

/*
Design a Recursive Descent Parser for the following grammar:
Query -> select Parameters Fclause Wclause
Parameters -> id ParametersPrime
ParametersPrime -> empty | , Parameters
Fclause -> from Parameters
Wclause -> where Exp
Exp -> id='Character'
Sample input: select a from T1 where a='c'
*/

void Query();
void Parameters();
void Parameters();
void ParametersPrime();
void Fclause();
void Wclause();
void Exp();

void invalid()
{
    if (!flag)
    {
        printf("Invalid\n");
        printf("row=%d , col=%d", tok.row, tok.col);
    }
}
void valid()
{
    printf("valid\n");
    exit(0);
}
void CheckAndGet()
{
    if (!unget)
    {
        tok = getNextToken(fp);
    }
    else
    {
        // whenever there is no invalid statement we set unget to 0
        unget = 0;
    }
}
void Query()
{
    CheckAndGet();
    if (strcmp("select", tok.token_name) == 0)
    {
        Parameters();
        Fclause();
        Wclause();
    }
    else
    {
        invalid();
        flag = 1;
    }
}

void Parameters()
{
    CheckAndGet();
    if (strcmp("id", tok.token_type) == 0)
    {
        ParametersPrime();
    }
    else
    {
        invalid();
        flag = 1;
    }
}

void ParametersPrime()
{
    CheckAndGet();
    if (strcmp(",", tok.token_name) == 0)
    {
        Parameters();
    }
    else
    {
        unget = 1;
    }
}

void Fclause()
{
    CheckAndGet();
    if (strcmp("from", tok.token_name) == 0)
    {
        Parameters();
    }
    else
    {
        invalid();
        flag = 1;
    }
}

void Wclause()
{
    CheckAndGet();
    if (strcmp("where", tok.token_name) == 0)
    {
        Exp();
    }
    else
    {
        invalid();
        flag = 1;
    }
}

void Exp()
{
    CheckAndGet();
    if (strcmp("id", tok.token_type) == 0)
    {
        CheckAndGet();
        if (strcmp("=", tok.token_name) == 0)
        {
            CheckAndGet();
            if (strcmp("\'", tok.token_name) == 0)
            {
                CheckAndGet();
                if (isalpha(tok.token_name[0]))
                {
                    CheckAndGet();
                    if (strcmp("\'", tok.token_name) == 0)
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
    fp = fopen("input.sql", "r");
    if (fp == NULL)
    {
        printf("CANT OPEN");
        exit(0);
    }

    Query();
    fclose(fp);
    return 0;
}