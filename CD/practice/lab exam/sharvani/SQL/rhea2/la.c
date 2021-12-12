#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
// Record point{
//     int a,b,c[10];
// }
int cnt = 1;
struct TOKEN
{
    char token_name[200];
    char token_type[200];
    int row, col;
};

char *keywords[] = {"Record", "int"};
char specialsymbols[] = {',', '[', ']', ';', '{', '}'};

void fillToken(struct TOKEN *tok, char *token_type, char *token_name)
{
    strcpy(tok->token_type, token_type);
    strcpy(tok->token_name, token_name);
    printf("token %d\n", cnt);
    cnt++;

    printf("<%s,%s>\n", token_type, token_name);
}

int isSpecialSymbol(char c)
{
    int len = 6;
    for (int i = 0; i < len; i++)
    {
        if (c == specialsymbols[i])
        {
            return 1;
        }
    }
    return 0;
}

int isKeyword(char *buffer)
{
    int len = 2;
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(buffer, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}
FILE *fp;
char c;
struct TOKEN getNextToken()
{
    struct TOKEN tok;
    int gotToken = 0;
    while ((c = fgetc(fp)) != EOF && !gotToken)
    {
        if (isSpecialSymbol(c))
        {
            char symbol[2];
            symbol[0] = c;
            symbol[1] = '\0';
            fillToken(&tok, "Special Symbol", symbol);
            {
                gotToken = 1;
            }
        }
        else if (isalpha(c))
        {
            char string[100];
            int k = 0;
            string[k++] = c;
            while ((c = fgetc(fp)) != EOF && isalnum(c))
            {
                string[k++] = c;
            }
            string[k] = '\0';

            fseek(fp, -1, SEEK_CUR);
            if (isKeyword(string))
            {
                fillToken(&tok, "Keyword", string);
                gotToken = 1;
            }
            else
            {
                fillToken(&tok, "id", string);
                gotToken = 1;
            }
        }
        else if (isdigit(c))
        {
            char numb[100];
            numb[0] = c;
            int k = 1;
            while ((c = fgetc(fp)) != EOF && isdigit(c))
            {
                numb[k++] = c;
            }
            fseek(fp, -1, SEEK_CUR);
            numb[k] = '\0';
            fillToken(&tok, "Number", numb);
        }
    }
    return tok;
}

int main()
{

    struct TOKEN tok;
    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        printf("cant open file");
        exit(0);
    }
    while (c != EOF)
    {
        tok = getNextToken(fp);
    }
    fclose(fp);
}