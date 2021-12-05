#include "la.h"
void program();
void declarations();
void datatype();

void idList();
void idListprime();
void idListprimePrime();

void stmtList();
void stmt();
void assignStat();
void expn();

void eprime();
void simpleExpn();

void seprime();

void term();

void tprime();

void factor();
void relop();
void addOp();
void mulOp();
void decStat();

void dPrime();

void loopStat();
void invalid();
struct token tkn;
FILE *file_ptr;
void invalid()
{
    printf("Error at row: %d, col: %d for token \"%s\"\n", tkn.row, tkn.col, tkn.token_name);
    printf("---------ERROR---------\n ");
    exit(0);
}
void program()
{
    tkn = getNextToken(file_ptr);
    if (strcmp("int", tkn.token_name) == 0 || strcmp("void", tkn.token_name) == 0)
    {
        tkn = getNextToken(file_ptr);
        if (strcmp(tkn.token_name, "main") == 0)
        {
            tkn = getNextToken(file_ptr);
            if (strcmp(tkn.token_name, "(") == 0)
            {
                tkn = getNextToken(file_ptr);
                if (strcmp(tkn.token_name, ")") == 0)
                {
                    tkn = getNextToken(file_ptr);
                    if (strcmp(tkn.token_name, "{") == 0)
                    {
                        tkn = getNextToken(file_ptr);
                        declarations();
                        stmtList();
                        if (strcmp(tkn.token_name, "}") == 0)
                        {
                            printf("----------Successfully compiled------------ \n");
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
    else
    {
        invalid();
    }
}
void declarations()
{
    if (isdtype(tkn.token_name) == 0)
        return;
    datatype();
    idList();
    if (strcmp(tkn.token_name, ";") == 0)
    {
        tkn = getNextToken(file_ptr);
        printf("%s", tkn.token_name);
        declarations();
    }
    else
    {
        invalid();
    }
}
void datatype()
{
    if (strcmp(tkn.token_name, "int") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else if (strcmp(tkn.token_name, "char") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else
    {
        invalid();
    }
}
void assignStat()
{
    if (strcmp(tkn.type, "Identifier") == 0)
    {
        tkn = getNextToken(file_ptr);
        if (strcmp(tkn.token_name, "=") == 0)
        {
            tkn = getNextToken(file_ptr);
            expn();
        }
        else
        {
            invalid();
        }
    }
    else
    {
        printf("here");
        invalid();
    }
}
void idList()
{
    if (strcmp(tkn.type, "Identifier") == 0)
    {
        printf("%s", tkn.token_name);
        tkn = getNextToken(file_ptr);
        printf("%s", tkn.token_name);

        idListprime();
    }
    else
    {
        invalid();
    }
}
void idListprime()
{
    if (strcmp(tkn.token_name, ",") == 0)
    {
        tkn = getNextToken(file_ptr);
        idList();
    }
    else if (strcmp(tkn.token_name, "=") == 0)
    {
        printf("Entered here");
        tkn = getNextToken(file_ptr);
        expn();
    }
    else if (strcmp(tkn.token_name, "[") == 0)
    {
        tkn = getNextToken(file_ptr);
        if (strcmp(tkn.type, "Number") == 0)
        {
            tkn = getNextToken(file_ptr);
            if (strcmp(tkn.token_name, "]") == 0)
            {
                tkn = getNextToken(file_ptr);
                idListprimePrime();
            }
            else
            {
                printf("here 7");
                invalid();
            }
        }
        else
        {
            printf("here 8");
            invalid();
        }
    }
}
void idListprimePrime()
{
    if (strcmp(tkn.token_name, ",") == 0)
    {
        tkn = getNextToken(file_ptr);
        idList();
    }
    else
        return;
}
void stmtList()
{
    if (strcmp(tkn.type, "Identifier") == 0 || strcmp(tkn.token_name, "if") == 0 ||
        strcmp(tkn.token_name, "for") == 0 || strcmp(tkn.token_name, "while") == 0)
    {
        stmt();
        stmtList();
    }
    return;
}
void stmt()
{
    if (strcmp(tkn.type, "Identifier") == 0)
    {
        assignStat();
        if (strcmp(tkn.token_name, ";") == 0)
        {
            tkn = getNextToken(file_ptr);
            return;
        }
        else
        {
            invalid();
        }
    }
    else if (strcmp(tkn.token_name, "if") == 0)
        decStat();
    else if ((strcmp(tkn.token_name, "while") == 0) || (strcmp(tkn.token_name, "for") == 0))
        loopStat();
    else
    {
        printf("%d.%d : Expected \" statement \"\n", tkn.row, tkn.col);
        exit(0);
    }
}
void expn()
{
    simpleExpn();
    eprime();
}
void eprime()
{
    if (strcmp(tkn.type, "RelationalOperator") != 0)
        return;
    relop();
    simpleExpn();
}
void simpleExpn()
{
    term();
    seprime();
}
void seprime()
{
    if ((strcmp(tkn.token_name, "+") != 0) && (strcmp(tkn.token_name, "-") != 0))
        return;
    addOp();
    term();
    seprime();
}
void term()
{
    factor();
    tprime();
}
void tprime()
{
    if ((strcmp(tkn.token_name, "*") != 0) && (strcmp(tkn.token_name, "/") != 0) &&
        (strcmp(tkn.token_name, "%") != 0))
        return;
    mulOp();
    factor();
    tprime();
}
void factor()
{
    if (strcmp(tkn.type, "Identifier") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else if (strcmp(tkn.type, "Number") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else
    {
        invalid();
    }
}
void relop()
{
    if (strcmp(tkn.token_name, "==") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else if (strcmp(tkn.token_name, "!=") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else if (strcmp(tkn.token_name, "<=") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else if (strcmp(tkn.token_name, ">=") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else if (strcmp(tkn.token_name, "<") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else if (strcmp(tkn.token_name, ">") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else
    {
        printf("here 4");
        invalid();
    }
}
void addOp()
{
    if (strcmp(tkn.token_name, "+") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else if (strcmp(tkn.token_name, "-") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else
    {
        printf("here 5");
        invalid();
    }
}
void mulOp()
{
    if (strcmp(tkn.token_name, "*") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else if (strcmp(tkn.token_name, "/") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else if (strcmp(tkn.token_name, "*") == 0)
    {
        tkn = getNextToken(file_ptr);
        return;
    }
    else
    {
        printf("here 6");
        invalid();
    }
}
void decStat()
{
    if (strcmp(tkn.token_name, "if") == 0)
    {
        tkn = getNextToken(file_ptr);
        if (strcmp(tkn.token_name, "(") == 0)
        {
            tkn = getNextToken(file_ptr);
            expn();
            if (strcmp(tkn.token_name, ")") == 0)
            {
                tkn = getNextToken(file_ptr);
                if (strcmp(tkn.token_name, "{") == 0)
                {
                    tkn = getNextToken(file_ptr);
                    stmtList();
                    if (strcmp(tkn.token_name, "}") == 0)
                    {
                        tkn = getNextToken(file_ptr);
                        dPrime();
                        return;
                    }
                    else
                    {
                    }
                    invalid();
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
void dPrime()
{
    if (strcmp(tkn.token_name, "else") == 0)
    {
        tkn = getNextToken(file_ptr);
        if (strcmp(tkn.token_name, "{") == 0)
        {
            tkn = getNextToken(file_ptr);
            stmtList();
            if (strcmp(tkn.token_name, "}") == 0)
            {
                tkn = getNextToken(file_ptr);
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
        return;
}
void loopStat()
{
    if (strcmp(tkn.token_name, "while") == 0)
    {
        tkn = getNextToken(file_ptr);
        if (strcmp(tkn.token_name, "(") == 0)
        {
            tkn = getNextToken(file_ptr);
            expn();
            if (strcmp(tkn.token_name, ")") == 0)
            {
                tkn = getNextToken(file_ptr);
                if (strcmp(tkn.token_name, "{") == 0)
                {
                    tkn = getNextToken(file_ptr);
                    stmtList();
                    if (strcmp(tkn.token_name, "}") == 0)
                    {
                        tkn = getNextToken(file_ptr);
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
    else if (strcmp(tkn.token_name, "for") == 0)
    {
        tkn = getNextToken(file_ptr);
        if (strcmp(tkn.token_name, "(") == 0)
        {
            tkn = getNextToken(file_ptr);
            assignStat();
            if (strcmp(tkn.token_name, ";") == 0)
            {
                tkn = getNextToken(file_ptr);
                expn();
                if (strcmp(tkn.token_name, ";") == 0)
                {
                    tkn = getNextToken(file_ptr);
                    assignStat();
                    if (strcmp(tkn.token_name, ")") == 0)
                    {
                        tkn = getNextToken(file_ptr);
                        if (strcmp(tkn.token_name, "{") == 0)
                        {
                            tkn = getNextToken(file_ptr);
                            stmtList();
                            if (strcmp(tkn.token_name, "}") == 0)
                            {
                                tkn = getNextToken(file_ptr);
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
        else
        {
            invalid();
        }
    }
}

int main()
{
    file_ptr = fopen("input.c", "r");
    if (!file_ptr)
    {
        printf("-----------File does not open-----------\n");
        return 0;
    }
    program();
    fclose(file_ptr);
}