#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZEhash 10

struct token
{
    char token_name[30];
    int row, col;
    char type[30];
};

struct symbTable
{
    char lex_name[30];
    char dtype[30];
    unsigned int size;
} symVal[SIZEhash];

int symInd = 0;

static int row = 1, col = 1;
char buf[1024];
const char specialsymbols[] = {'?', ';', ':', ',', '(', ')', '{', '}', '[', ']'};
const char *Keywords[] = {"main", "void", "const", "char", "int", "return", "for", "while", "do", "switch", "if", "else", "unsigned", "case", "break", "double", "float"};
const char arithmeticsymbols[] = {'*'};
char dtype[100];
const char *dataType[] = {"int", "float", "double", "char", "void"};
int isKeyword(const char *str)
{
    for (int i = 0; i < sizeof(Keywords) / sizeof(char *); i++)
    {
        if (strcmp(str, Keywords[i]) == 0)
            return 1;
    }
    return 0;
}
int charBelongsTo(int c, const char *arr)
{
    int len;
    if (arr == specialsymbols)
        len = sizeof(specialsymbols) / sizeof(char);
    else if (arr == arithmeticsymbols)
        len = sizeof(arithmeticsymbols) / sizeof(char);
    for (int i = 0; i < len; i++)
    {
        if (c == arr[i])
            return 1;
    }
    return 0;
}

//getting data type size
int dtypeSize(char dtype[30])
{
    int i;
    for (i = 0; i < sizeof(dataType) / sizeof(char *); ++i)
    {
        if (strcmp(dtype, dataType[i]) == 0)
        {
            break;
        }
    }
    switch (i)
    {
    case 0:
        return sizeof(int);
        break;
    case 1:
        return sizeof(float);
        break;
    case 2:
        return sizeof(double);
    case 3:
        return sizeof(char);
    case 4:
        return sizeof(void);
    default:
        return -1;
        break;
    }
}

void fillToken(struct token *tkn, char c, int row, int col, char *type)
{
    tkn->row = row;
    tkn->col = col;
    strcpy(tkn->type, type);
    tkn->token_name[0] = c;
    tkn->token_name[1] = '\0';
}

int searchTable(char lex[30])
{
    for (int i = 0; i < symInd; ++i)
    {
        if (strcmp(lex, symVal[i].lex_name) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void insertTable(char lex[30], char dtype[30], int flag)
{
    int searchVal = searchTable(lex);
    if (searchVal == 1)
    {
        return;
    }
    strcpy(symVal[symInd].lex_name, lex);
    if (flag == 0)
    {
        symVal[symInd].size = dtypeSize(dtype);
        strcpy(symVal[symInd].dtype, dtype);
    }
    else
    {
        symVal[symInd].size = -1;
        strcpy(symVal[symInd].dtype, "function");
    }
    ++symInd;
}

void newLine()
{
    ++row;
    col = 1;
}
struct token getNextToken(FILE *fin)
{
    int c;
    struct token tkn = {.row = -1};
    int gotToken = 0;
    while (!gotToken && (c = fgetc(fin)) != EOF)
    {
        //special symbol
        if (charBelongsTo(c, specialsymbols))
        {
            fillToken(&tkn, c, row, col, "Special Symbol");
            gotToken = 1;
            ++col;
        }
        //arithmetic operator
        else if (charBelongsTo(c, arithmeticsymbols))
        {
            fillToken(&tkn, c, row, col, "ArithmeticOperator");
            gotToken = 1;
            ++col;
        }
        //check if + or ++
        else if (c == '+')
        {
            int d = fgetc(fin);
            if (d != '+')
            {
                fillToken(&tkn, c, row, col, "ArithmeticOperator");
                gotToken = 1;
                ++col;
                fseek(fin, -1, SEEK_CUR);
            }
            else
            {
                fillToken(&tkn, c, row, col, "UnaryOperator");
                strcpy(tkn.token_name, "++");
                gotToken = 1;
                col += 2;
            }
        }
        //check if - or --
        else if (c == '-')
        {
            int d = fgetc(fin);
            if (d != '-')
            {
                fillToken(&tkn, c, row, col, "ArithmeticOperator");
                gotToken = 1;
                ++col;
                fseek(fin, -1, SEEK_CUR);
            }
            else
            {
                fillToken(&tkn, c, row, col, "UnaryOperator");
                strcpy(tkn.token_name, "--");
                gotToken = 1;
                col += 2;
            }
        }
        //check if = or ==
        else if (c == '=')
        {
            int d = fgetc(fin);
            if (d != '=')
            {
                fillToken(&tkn, c, row, col, "AssignmentOperator");
                gotToken = 1;
                ++col;
                fseek(fin, -1, SEEK_CUR);
            }
            else
            {
                fillToken(&tkn, c, row, col, "RelationalOperator");
                strcpy(tkn.token_name, "==");
                gotToken = 1;
                col += 2;
            }
        }
        //check if number
        else if (isdigit(c))
        {
            tkn.row = row;
            tkn.col = col++;
            tkn.token_name[0] = c;
            int k = 1;
            while ((c = fgetc(fin)) != EOF && isdigit(c))
            {
                tkn.token_name[k++] = c;
                col++;
            }
            tkn.token_name[k] = '\0';
            strcpy(tkn.type, "Number");
            gotToken = 1;
            fseek(fin, -1, SEEK_CUR);
        }
        //to remove preprocessor directives
        else if (c == '#')
        {
            while ((c = fgetc(fin)) != EOF && c != '\n')
                ;
            newLine();
        }
        else if (c == '\n')
        {
            newLine();
            c = fgetc(fin);
            if (c == '#')
            {
                while ((c = fgetc(fin)) != EOF && c != '\n')
                    ;
                newLine();
            }
            else if (c != EOF)
                fseek(fin, -1, SEEK_CUR);
        }
        else if (isspace(c))
            ++col;
        //check if identifier
        else if (isalpha(c) || c == '_')
        {
            tkn.row = row;
            tkn.col = col++;
            tkn.token_name[0] = c;
            int k = 1;
            while ((c = fgetc(fin)) != EOF && isalnum(c))
            {
                tkn.token_name[k++] = c;
                ++col;
            }
            tkn.token_name[k] = '\0';
            if (isKeyword(tkn.token_name))
            {
                strcpy(tkn.type, "Keyword");
                strcpy(dtype, tkn.token_name); //changes from here
            }
            else
            {
                strcpy(tkn.type, "Identifier"); //changes from here
                // c = getc(fin);
                if (c == '(')
                {
                    //function
                    insertTable(tkn.token_name, dtype, 1);
                }
                else
                {
                    //identifier
                    insertTable(tkn.token_name, dtype, 0);
                }
                strcpy(tkn.token_name, "ID"); //changes till here
            }
            gotToken = 1;
            fseek(fin, -1, SEEK_CUR);
        }
        //check for comments or operator
        else if (c == '/')
        {
            int d = fgetc(fin);
            ++col;
            if (d == '/')
            {
                while ((c = fgetc(fin)) != EOF && c != '\n')
                    ++col;
                if (c == '\n')
                    newLine();
            }
            else if (d == '*')
            {
                do
                {
                    if (d == '\n')
                        newLine();
                    while ((c == fgetc(fin)) != EOF && c != '*')
                    {
                        ++col;
                        if (c == '\n')
                            newLine();
                    }
                    ++col;
                } while ((d == fgetc(fin)) != EOF && d != '/' && (++col));
                ++col;
            }
            else
            {
                fillToken(&tkn, c, row, --col, "ArithmeticOperator");
                gotToken = 1;
                fseek(fin, -1, SEEK_CUR);
            }
        }
        //string literal
        else if (c == '"')
        {
            tkn.row = row;
            tkn.col = col;
            strcpy(tkn.type, "StringLiteral");
            int k = 1;
            tkn.token_name[0] = '"';
            while ((c = fgetc(fin)) != EOF && c != '"')
            {
                tkn.token_name[k++] = c;
                ++col;
            }
            tkn.token_name[k] = '"';
            gotToken = 1;
        }
        //RelOp or Logical OP
        else if (c == '<' || c == '>' || c == '!')
        {
            fillToken(&tkn, c, row, col, "RelationalOperator");
            ++col;
            int d = fgetc(fin);
            if (d == '=')
            {
                ++col;
                strcat(tkn.token_name, "=");
            }
            else
            {
                if (c == '!')
                    strcpy(tkn.type, "LogicalOperator");
                fseek(fin, -1, SEEK_CUR);
            }
            gotToken = 1;
        }
        else if (c == '&' || c == '|')
        {
            int d = fgetc(fin);
            if (c == d)
            {
                tkn.token_name[0] = tkn.token_name[1] = c;
                tkn.token_name[2] = '\0';
                tkn.row = row;
                tkn.col = col;
                ++col;
                gotToken = 1;
                strcpy(tkn.type, "LogicalOperator");
            }
            else
                fseek(fin, -1, SEEK_CUR);
            ++col;
        }
        else
            ++col;
    }
    return tkn;
}
// int main()
// {
//     FILE *fin = fopen("input.c", "r");
//     if (!fin)
//     {
//         printf("Error! File cannot be opened!\n");
//         return 0;
//     }
//     struct token tkn;
//     while ((tkn = getNextToken(fin)).row != -1)
//         printf("<%s, %d, %d>\n", tkn.token_name, tkn.row, tkn.col);
//     printf("\nThe size value -1 indicates it is a function\n");
//     printf("\nindex lexeme dataType size\n");
//     for(int i = 0; i<symInd; ++i){
//         printf("%d  %s  %s  %d\n",i,symVal[i].lex_name,symVal[i].dtype,symVal[i].size);
//     }
//     fclose(fin);
// }