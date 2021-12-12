#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct TOKEN
{
    char token_name[20];
    char token_type[20];
    int row, col;
};

int row = 1, col = 1;
char specialsymbols[] = {',', '\'', '='};
char *keywords[] = {"where", "select", "from"};

void fillToken(struct TOKEN *tok, int row, int col, char *token_type, char *token_name)
{
    printf("fill token\n");
    tok->col = col;
    tok->row = row;
    strcpy(tok->token_type, token_type);
    strcpy(tok->token_name, token_name);
    printf("<%s | %s | %d | %d>\n", tok->token_type, tok->token_name, row, col);
}

int isSpecialSymbol(char c)
{
    int len = 3;
    for (int i = 0; i < len; i++)
    {
        if (c == specialsymbols[i])
        {
            return 1;
        }
    }
    return 0;
}

int isKeyWord(char *buffer)
{
    int len = 3;
    for (int i = 0; i < len; i++)
    {
        if (strcmp(buffer, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void newLine()
{
    row++;
    col = 1;
}

struct TOKEN getNextToken(FILE *fp, char c)
{
    struct TOKEN tok;
    int gotToken = 0;
    // char c;
    tok.row = -1;
    while ((c = fgetc(fp)) != EOF && !gotToken)
    {
        if (isspace(c))
        {
            ++col;
        }
        if (c == '\n')
        {
            newLine();
        }
        if (isSpecialSymbol(c))
        {
            char symbol[2];
            symbol[0] = c;
            symbol[1] = '\0';
            fillToken(&tok, row, col, "SpecialSymbol", symbol);
            gotToken = 1;
            ++col;
        }
        else if (isalpha(c))
        {
            char buffer[100];
            int k = 0;
            buffer[k++] = c;

            while ((c = fgetc(fp)) != EOF && isalnum(c))
            {
                buffer[k++] = c;
            }
            buffer[k] = '\0';
            fseek(fp, -1, SEEK_CUR);
            if (isKeyWord(buffer))
            {
                fillToken(&tok, row, col, "Keyword", buffer);
                col += strlen(buffer);
                gotToken = 1;
            }
            else
            {
                fillToken(&tok, row, col, "id", buffer);
                col += strlen(buffer);
                gotToken = 1;
            }
        }
        else
        {
            ++col;
        }
    }

    return tok;
}

// int main()
// {
//     FILE *fp;
//     fp = fopen("input.sql", "r");
//     if (fp == NULL)
//     {
//         printf("cant iopen");
//         exit(0);
//     }
//     char c;
//     struct TOKEN tok;
//     while (c != EOF)
//     {
//         tok = getNextToken(fp, c);
//     }
//     fclose(fp);
// }