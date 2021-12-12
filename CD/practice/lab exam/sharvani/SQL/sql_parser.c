#include "sql_la.h"

#define INPUT "input.sql"

/*
Design a Recursive Descent Parser for the following grammar:
Query -> select Parameters Fclause Wclause
Parameters -> id | id, Parameters
Fclause -> from Parameters
Wclause -> where Exp
Exp -> id='Character'
Sample input: select a from T1 where a='c'
*/
int flag = 0;
int unget = 0;
FILE *fp;

void Query();
void Parameters();
void ParametersPrime();
void Fclause();
void Wclause();
void Exp();

void Valid()
{
    printf("\n****************SUCCESS**************************\n");
}

void Invalid()
{
    if (!flag)
        printf("**********ERROR*********************\n");
}
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

struct TOKEN tok;
void checkAndGet()
{
    if (!unget)
    {
        tok = getNextToken(fp);
    }
    else
    {
        unget = 0;
    }
}
void Query()
{
    checkAndGet();
    if (strcmp("select", tok.token_name) == 0)
    {
        Parameters();
        Fclause();
        Wclause();
    }
    else
    {
        Invalid();
        flag = 1;
    }
}
void Parameters()
{
    checkAndGet();
    if (strcmp("id", tok.token_type) == 0)
    {
        ParametersPrime();
    }
    else
    {
        Invalid();
        flag = 1;
    }
}
void ParametersPrime()
{
    checkAndGet();
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
    checkAndGet();
    if (strcmp("from", tok.token_name) == 0)
    {
        Parameters();
    }
    else
    {
        Invalid();
        flag = 1;
    }
}

void Wclause()
{
    checkAndGet();
    if (strcmp("where", tok.token_name) == 0)
    {
        Exp();
    }
    else
    {
        Invalid();
        flag = 1;
    }
}
// Exp -> id='Character'
void Exp()
{
    checkAndGet();
    if (strcmp("id", tok.token_type) == 0)
    {
        checkAndGet();
        if (strcmp("=", tok.token_name) == 0)
        {
            checkAndGet();
            if (strcmp("\'", tok.token_name) == 0)
            {
                checkAndGet();
                if (isalpha(tok.token_name[0]))
                {
                    checkAndGet();
                    if (strcmp("\'", tok.token_name) == 0)
                    {
                        Valid();
                    }
                    else
                    {
                        Invalid();
                        flag = 1;
                    }
                }
                else
                {
                    Invalid();
                    flag = 1;
                }
            }
            else
            {
                Invalid();
                flag = 1;
            }
        }
        else
        {
            Invalid();
            flag = 1;
        }
    }
    else
    {
        Invalid();
        flag = 1;
    }
}

FILE *fp;

int main()
{

    fp = fopen(INPUT, "r");
    Query();
    fclose(fp);
    return 0;
}