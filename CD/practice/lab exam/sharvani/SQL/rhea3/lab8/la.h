#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZEhash 10

struct token
{
    char token_name[30];
    int row, col;
    char token_type[30];
};

// int main()
// {
//     int a, c;
//     char hello;
//     a = c;
//     a = b;
// }

char *keywords[]={"int","main","char"};
char specialsymbols[]={'{','}',';','(',')'}