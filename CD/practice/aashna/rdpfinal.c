#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include "la.h"
char c;
char buf[100];
struct token tok;

FILE *f1;
void Program();
void declarations();
void datatype();

void Program()
{

    tok = getNextToken(f1);

    if (strcmp(tok.token_name, "main") == 0)
    {

        tok = getNextToken(f1);

        if (strcmp(tok.token_name, "(") == 0)
        {
            tok = getNextToken(f1);

            if (strcmp(tok.token_name, ")") == 0)
            {
                tok = getNextToken(f1);

                if (strcmp(tok.token_name, "{") == 0)
                {
                    tok = getNextToken(f1);

                    declarations();
                    stmtlist();
                    tok = getNextToken(f1);

                    if (strcmp(tok.token_name, "}") == 0)
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

    datatype();
    identifierlist();

    tok = getNextToken(f1);

    if (strcmp(tok.token_name, ";") == 0)
    {
        tok = getNextToken(f1);
        declarations();
    }
    else
    {
        invalid();
    }
}

void stmtlist()
{

    tok = getNextToken(f1);
    if((strcmp(tok.type,"Identifier")==0) || (strcmp(tok.token_name,"if")==0) ||(strcmp(tok.token_name,"for")==0) || (strcmp(tok.token_name,"while")==0))
    {

    stmt();
    stmtlist();
    }
    
}

void stmt()
{
    tok=getNextToken(f1);

    if((strcmp(tok.type,"Identifier")) 
    {
        assignstat();
        if((strcmp(";",tok.token_name)==0))
        {
            return;
        }
        else
        {
            
            invalid();
        }
        
    }
    else if((strcmp(tok.token_name,"if")))
    {
        decisionstat();

    }
    else if((strcmp(tok.token_name,"while"))|| (strcmp(tok.token_name,"for")))
    {
        loopstat();
    }
    else
    {
        
        invalid();
    }
    

}

identifierlist()
{

    if (strcmp(tok.type, "Identifier") == 0)
    {

        tok = getNextToken(f1);
        idlistprime();
    }
    else
    {
        invalid();
    }
}

void idlistprime()
{
    if (strcmp(tok.token_name, ",") == 0)

    {
        tok = getNextToken(f1);
        identifierlist();
    }

    else if (strcmp(tok.token_name, "[") == 0)
    {
        tok = getNextToken(f1);

        if (strcmp(tok.type, "Number") == 0)
        {

            tok = getNextToken(f1);
            if (strcmp(tok.token_name, "]") == 0)
            {
                tok = getNextToken(f1);
                idlistprimeprime();
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

void idlistprimeprime()
{

    if (strcmp(tok.token_name, ",") == 0)
    {
        tok = getNextToken(f1);
        identifierlist();
    }
}

int main()
{
    f1 = fopen("input.c", "r");

    Program();
    if ((c = fgetc(f1)) == EOF)
    {
        valid();
    }
    else
    {
        invalid();
    }

    return 0;
}