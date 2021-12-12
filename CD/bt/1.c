#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("%d", sizeof(char *));
    char *msg[] = {"Rhea", "Minni", "wegnjowgboewri"};
    printf("%d\n", sizeof(msg));
    for (int i = 0; i < 2; i++)
        printf("%d\n", sizeof(msg) / sizeof(char *));
}