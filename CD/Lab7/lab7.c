#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <la.c>
FILE *fin;
struct token tkn;

void Program();
void declaration();
void assign_stat();
void data_type();
void identifier_list();
void IDListprime();
void assign_statPrime();

void invalid()
{
    printf("error at row: %d, col: %d for token \"%s\"\n", tkn.row, tkn.col, tkn.token_name);
    printf("-----------------ERROR!----------------\n");
    exit(0);
}

void valid()
{
    printf("----------------SUCCESS!---------------\n");
    exit(0);
}

void Program()
{
    tkn = getNextToken(fin);
    if (strcmp("int", tkn.token_name) == 0 || strcmp("void", tkn.token_name) == 0)
    {
        tkn = getNextToken(fin);
        if (strcmp("main", tkn.token_name) == 0)
        {
            tkn = getNextToken(fin);
            if (strcmp("(", tkn.token_name) == 0)
            {
                tkn = getNextToken(fin);
                if (strcmp(")", tkn.token_name) == 0)
                {
                    tkn = getNextToken(fin);
                    if (strcmp("{", tkn.token_name) == 0)
                    {
                        declaration();
                        assign_stat();
                        tkn = getNextToken(fin);
                        if (strcmp("}", tkn.token_name) == 0)
                        {
                            valid();
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

void declaration()
{

    data_type();
    identifier_list();
    tkn = getNextToken(fin);
    if (strcmp(";", tkn.token_name) == 0)
    {
        declaration();
    }
}

void data_type()
{
    tkn = getNextToken(fin);
    if (strcmp("int", tkn.token_name) == 0 || strcmp("char", tkn.token_name) == 0)
    {
        return;
    }
    else
    {
        invalid();
    }
}

void identifier_list()
{
    tkn = getNextToken(fin);
    if (strcmp("ID", tkn.token_name) == 0)
    {
        IDListprime();
    }
    else
    {
        invalid();
    }
}

void IDListprime()
{
    tkn = getNextToken(fin);
    if (strcmp(",", tkn.token_name) == 0)
    {
        identifier_list();
    }
}

void assign_stat()
{
    // tkn = getNextToken(fin);

    if (strcmp("ID", tkn.token_name) == 0)
    {
        tkn = getNextToken(fin);
        if (strcmp("=", tkn.token_name) == 0)
        {
            assign_statPrime();
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

void assign_statPrime()
{
    tkn = getNextToken(fin);
    if (strcmp("ID", tkn.token_name) == 0)
    {
        tkn = getNextToken(fin);
        if (strcmp(";", tkn.token_name) == 0)
        {
            return;
        }
        else
        {
            invalid();
        }
    }
    else if (sizeof(atoi(tkn.token_name)) == sizeof(int))
    {
        tkn = getNextToken(fin);
        if (strcmp(";", tkn.token_name) == 0)
        {
            return;
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

int main()
{
    fin = fopen("input.c", "r");
    if (!fin)
    {
        printf("Error! File cannot be opened!\n");
        return 0;
    }
    Program();
    fclose(fin);
}
