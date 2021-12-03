#include <stdio.h>
#include <stdlib.h>
int curr = 0;
char str[100];

void valid()
{
    printf("valid!\n");
    exit(0);
}

void invalid()
{
    printf("invalid!\n");
    exit(0);
}

void E()
{
    T();
    Eprime();
}

void Eprime()
{
    if (str[curr] == '+')
    {
        curr++;
        T();
        Eprime();
    }
}

void T()
{
    F();
    Tprime();
}

void Tprime()
{
    if (str[curr] == '*')
    {
        curr++;
        F();
        Tprime();
    }
}

void F()
{
    if (str[curr] == '(')
    {
        curr++;
        E();
        if (str[curr] == ')')
        {
            curr++;
            return;
        }
    }
    else if (str[curr] == 'i')
    {
        curr++;
        return;
    }
    else
    {
        invalid();
    }
}

int main()
{
    printf("Enter a string\n");
    scanf("%s", str);
    E();
    if (str[curr] == '$')
    {
        valid();
    }
    else
    {
        invalid();
    }
}