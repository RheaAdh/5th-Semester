#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>

struct TOKEN
{
    char token_name[30];
    char token_type[30];
    int row, col;
};

char c;
int row = 1;
int col = 1;
const char specialsymbols[] = {
    '?',
    ';',
    ':',
    ',',
    '(',
    ')',
    '{',
    '}',
    '[',
    ']'};
const char *Keywords[] = {
    "main",
    "void",
    "const",
    "char",
    "int",
    "return",
    "if",
    "else",
    "unsigned",
    "break",
};

char dtype[100];
const char *dataType[] = {"int", "char"};

struct TOKEN getNextToken(FILE *fp)
{
    
}
