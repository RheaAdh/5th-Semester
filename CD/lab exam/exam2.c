// Rd parser for this grammar

// Query -> select paramList Fclause Wclause
// Fclause -> from paramList
// Wclause -> where id='character'

// paramList -> id | id, paramList
// we left factor it to these

// paramList->id paramList'
// paramList ->empty | ,paramList

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int curr = 0;
char str[100] = "select aeheh234,sdgew from T1,T2 where a='c'$";

void Query();
void paramList();
void paramListPrime();
void Fclause();
void Wclause();
void Exp();

void invalid()
{
    printf("-----------------ERROR!----------------\n");
    exit(0);
}
void valid()
{
    printf("----------------SUCCESS!---------------\n");
    exit(0);
}

void Query()
{
    printf("Query\n");
    if (str[curr] == 's')
    {
        curr++;
        if (str[curr] == 'e')
        {
            curr++;
            if (str[curr] == 'l')
            {
                curr++;
                if (str[curr] == 'e')
                {
                    curr++;
                    if (str[curr] == 'c')
                    {
                        curr++;
                        if (str[curr] == 't')
                        {
                            curr++;
                            while (str[curr] == ' ')
                                curr++;
                            paramList();
                            Fclause();
                            Wclause();
                        }
                        else
                        {
                            invalid();
                        }
                    }
                    else
                    {
                        invalid();
                    }
                }
                else
                {
                    invalid();
                }
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}

void paramList()
{
    printf("paramList\n");
    while (str[curr] == ' ')
        curr++;
    while (isalnum(str[curr]))
        curr++;
    while (str[curr] == ' ')
        curr++;
    paramListPrime();
}

void paramListPrime()
{
    printf("paramListPrime\n");
    while (str[curr] == ' ')
        curr++;
    if (str[curr] == ',')
    {
        curr++;
        paramList();
    }
}

void Fclause()
{
    printf("Fclause\n");
    while (str[curr] == ' ')
        curr++;
    if (str[curr] == 'f')
    {
        curr++;
        if (str[curr] == 'r')
        {
            curr++;
            if (str[curr] == 'o')
            {
                curr++;
                if (str[curr] == 'm')
                {
                    curr++;
                    while (str[curr] == ' ')
                        curr++;
                    paramList();
                }
                else
                {
                    invalid();
                }
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}

void Wclause()
{
    printf("Wclause\n");
    while (str[curr] == ' ')
        curr++;
    if (str[curr] == 'w')
    {
        curr++;
        if (str[curr] == 'h')
        {
            curr++;
            if (str[curr] == 'e')
            {
                curr++;
                if (str[curr] == 'r')
                {
                    curr++;
                    if (str[curr] == 'e')
                    {
                        curr++;
                        while (str[curr] == ' ')
                            curr++;
                        Exp();
                    }
                    else
                    {
                        invalid();
                    }
                }
                else
                {
                    invalid();
                }
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}

void Exp()
{
    printf("Exp \n%c\n", str[curr]);
    while (str[curr] == ' ')
        curr++;
    while (isalnum(str[curr]))
        curr++;
    printf("%c\n", str[curr]);
    while (str[curr] == ' ')
        curr++;
    printf("%c\n", str[curr]);
    if (str[curr] == '=')
    {

        curr++;
        printf("%c\n", str[curr]);
        while (str[curr] == ' ')
            curr++;
        if (str[curr] == '\'')
        {
            curr++;
            printf("%c\n", str[curr]);
            while (isalnum(str[curr]))
                curr++;
            printf("%c\n", str[curr]);
            if (str[curr] == '\'')
            {
                curr++;
                printf("%c\n", str[curr]);
                return;
            }
            else
            {
                printf("1");
                invalid();
            }
        }
        else
        {
            printf("2");
            invalid();
        }
    }
    else
    {
        printf("3");
        invalid();
    }
}
int main()
{
    // FILE *fp;
    // fp = fopen("input.txt", "r");
    // if (fp == NULL)
    // {
    //     printf("Cannot open file \n");
    //     exit(0);
    // }
    // fgets(str, 100, fp);

    printf("%s\n", str);
    Query();
    if (str[curr] == '$')
        valid();
    else
        invalid();
}