/*
Design a Recursive Descent Parser for the following grammar:
Query -> select Parameters Fclause Wclause
Parameters -> id | id, Parameters
Fclause -> from Parameters
Wclause -> where Exp
Exp -> id='Character'
Sample input: select a from T1 where a='c'
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//#define INPUT "input.sql"

const char *keywords[] = {"select", "from", "where"};
char special_symbols[] = {',', '=', '\''};
int row = 1, col = 1;
char buffer[256];

struct TOKEN
{
    char token_name[50];
    int row, col;
    char token_type[50];
};
struct st
{
    char lex_name[20];
    char lex_type[20];
};
struct st symTable[10];
int symIdx = 0;
void insertToken(char *lex_name, char *lex_type)
{
    strcpy(symTable[symIdx].lex_name, lex_name);
    strcpy(symTable[symIdx].lex_type, lex_type);
    symIdx++;
}

int isSpecial(char c)
{
    int len = 3;
    //len = sizeof(special_symbols)/sizeof(char);

    for (int i = 0; i < len; ++i)
    {
        if (c == special_symbols[i])
            return 1;
    }
    return 0;
}

int iskeyword(char *w)
{
    for (int i = 0; i < 3; ++i)
    {
        if (strcmp(keywords[i], w) == 0)
            return 1;
    }
    return 0;
}

void newLine()
{
    ++row;
    col = 1;
}

void make_token(struct TOKEN *tkn, int r, int c, char *lex, char *type)
{
    strcpy(tkn->token_name, lex);
    strcpy(tkn->token_type, type);
    tkn->row = r;
    tkn->col = c;
    printf("<%s,%d,%d,%s>\n", tkn->token_name, tkn->row, tkn->col, tkn->token_type);
}

struct TOKEN getNextToken(FILE *fp)
{
    char c;
    int gotToken = 0;
    struct TOKEN token;
    token.row = -1;

    while ((c = fgetc(fp)) != EOF && !gotToken)
    {
        //printf("scanned %c:\t",c);
        if (isspace(c))
        {
            ++col;
        }

        if (c == '\n')
        {
            newLine();
        }

        if (isSpecial(c))
        {
            char symbol[2];
            symbol[0] = c;
            symbol[1] = '\0';
            make_token(&token, row, col, symbol, "Special Symbol");
            col += 1;
            gotToken = 1;
        }

        else if (isalpha(c))
        {
            int k = 0;
            char string[256];
            string[k++] = c;

            while ((c = fgetc(fp)) != EOF && isalnum(c))
            {
                string[k++] = c;
            }
            //printf("%c\t",c);
            fseek(fp, -1, SEEK_CUR);
            //c=fgetc(fp);
            //printf("%c\t",c);
            //fseek(fp,-1,SEEK_CUR);
            string[k] = '\0';
            //printf("%s\n",string);

            if (iskeyword(string))
            {
                make_token(&token, row, col, string, "keyword");
                col += strlen(string);
                gotToken = 1;
            }

            else
            {
                make_token(&token, row, col, string, "id");
                col += strlen(string);
                gotToken = 1;
            }
            insertToken(string, token.token_type);
        }

        else
        {
            ++col;
        }
    }

    return token;
}

int main()
{

    FILE *f1 = fopen("input.c", "r");
    int i;

    struct TOKEN token1;
    while ((token1 = getNextToken(f1)).row != -1)
    {

        printf("<%s,%d,%d,%s>\n", token1.token_name, token1.row, token1.col, token1.token_type);
    }
    printf("SYMBOL          TYPE \n");
    printf("-------------------------\n");
    for (i = 0; i < symIdx; i++)
    {
        printf("%s               %s \n", symTable[i].lex_name, symTable[i].lex_type);
    }
    return 0;
}
