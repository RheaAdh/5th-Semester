#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include "la.h"

struct TOKEN tok;
FILE *fp;

void invalid()
{
    printf("Error at row: %d, col: %d for token \"%s\"\n", tok.row, tok.col, tok.token_name);
    printf("---------ERROR---------\n ");
    exit(0);
}

void Program()
{
    tok = getNextToken(fp);
    if (strcmp(tok.token_name, "int") == 0 || strcmp(tok.token_name, "void") == 0)
    {
        tok = getNextToken(fp);
        if (strcmp(tok.token_name, "main") == 0)
        {
            tok = getNextToken(fp);
            if (strcasecmp("(", tok.token_name) == 0)
            {
                tok = getNextToken(fp);
                if (strcmp(")", tok.token_name) == 0)
                {
                    tok = getNextToken(fp);
                    if (strcmp("{", tok.token_name) == 0)
                    {
                        tok = getNextToken(fp);
                        declarations();
                        assign_stat();
                        if (strcmp("}", tok.token_name) == 0)
                        {
                            printf("SUCCESSFULLY COMPILED!\n");
                            return;
                        }
                        else
                        {
                            invalid();
                        }
                    }
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

void declarations()
{
    tok = getNextToken(fp);
    if (strcmp("int", tok.token_name) == 0 || strcmp(tok.token_name, "char") == 0)
    {
        datatype();
        identifierList();
        if (strcmp(";", tok.token_name) == 0)
        {
            tok = getNextToken(fp);
            declarations();
        }
    }
    else
    {
        invalid();
    }
}

void datatype()
{
    if (strcmp("int", tok.token_name) == 0)
    {
        tok = getNextToken(fp);
        return;
    }
    else if (strcmp("char", tok.token_name) == 0)
    {
        tok = getNextToken(fp);
        return;
    }
    else
    {
        invalid();
    }
}

void identifierList()
{
    if (strcmp("Identifier", tok.token_type) == 0)
    {
        tok = getNextToken(fp);
        identifierListPrime();
    }
    else
    {
        invalid();
    }
}

void identifierListPrime()
{
    if (strcmp(",", tok.token_name) == 0)
    {
        tok = getNextToken(fp);
        identifierList();
    }
}

void assignStat()
{
    if (strcmp("Identifier", tok.token_type) == 0)
    {
        tok = getNextToken(fp);
        if (strcmp("=", tok.token_name) == 0)
        {
            assignStatPrime();
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

void assignStatPrime()
{
    if (strcmp("Identifier", tok.token_type) == 0)
    {
        tok = getNextToken(fp);
        if (strcmp(";", tok.token_name) == 0)
        {
            return;
        }
        else
        {
            invalid();
        }
    }
    else if (strcmp("Number", tok.token_type) == 0)
    {
        tok = getNextToken(fp);
        if (strcmp(";", tok.token_name) == 0)
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

    fp = fopen("input.c", "r");
    if (fp == NULL)
    {
        printf("CANNOT OPEN FILE");
        exit(0);
    }
    printf("FILE OPENED!\n");

    Program();
}