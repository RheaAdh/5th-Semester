// Rd parser for this grammar

// Query -> select paramList Fclause Wclause
// Fclause -> from paramList
// Wclause -> where id='character'

// paramList -> id | id, paramList
// we left factor it to these

// paramList->id paramList'
// paramList ->empty | ,paramList

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void query();
void parameters();
void parametersPrime();
void fClause();
void wClause();
void Exp();
int id();

/*
Not working
File reading, change the string below
multiple parameters (i.e id,id) does not get matched

Not efficient
Character by character checking
Some places need to increment curr by 2 to avoid the spaces
*/

void valid()
{
    printf("----Success----\n");
    exit(0);
}
void invalid(int d)
{
    printf("----Error----%d\n", d);
    exit(0);
}

int curr = 0;
char str[200] = "Select id from id where id='Character'";
// char str[200] = calloc(sizeof(char), 200);

int id()
{
    if (str[curr] == 'i')
    {
        curr++;
        if (str[curr] == 'd')
        {
            return 1;
        }
        else
            invalid(0);
    }
    else
        invalid(0);
}

void query()
{
    if (str[curr] == 'S')
    {
        curr++;
        if (str[curr] == 'e')
        {
            curr++;
            if (str[curr] == 'l')
            {
                curr++;
                if (str[curr] == 'e')
                {
                    curr++;
                    if (str[curr] == 'c')
                    {
                        curr++;
                        if (str[curr] == 't')
                        {
                            curr = curr + 2;
                            ;
                            parameters();
                            fClause();
                            wClause();
                        }
                        else
                            invalid(1);
                    }
                    else
                        invalid(1);
                }
                else
                    invalid(1);
            }
            else
                invalid(1);
        }
        else
            invalid(1);
    }
    else
        invalid(1);
}

void parameters()
{
    if (id())
    {
        curr++;
        curr++;
        //parametersPrime();
        return;
    }
    else
        invalid(2);
}

void parametersPrime()
{
    if (str[curr] == ',')
    {
        curr++;
        if (id())
        {
            curr++;
            parametersPrime();
        }
    }
    else
        invalid(3);
}

void fClause()
{
    if (str[curr] == 'f')
    {
        curr++;
        if (str[curr] == 'r')
        {
            curr++;
            if (str[curr] == 'o')
            {
                curr++;
                if (str[curr] == 'm')
                {
                    curr = curr + 2;
                    parameters();
                }
                else
                    invalid(4);
            }
            else
                invalid(4);
        }
        else
            invalid(4);
    }
    else
        invalid(4);
    return;
}

void wClause()
{
    if (str[curr] == 'w')
    {
        curr++;
        if (str[curr] == 'h')
        {
            curr++;
            if (str[curr] == 'e')
            {
                curr++;
                if (str[curr] == 'r')
                {
                    curr++;
                    if (str[curr] == 'e')
                    {
                        curr = curr + 2;
                        Exp();
                    }
                    else
                        invalid(5);
                }
                else
                    invalid(5);
            }
            else
                invalid(5);
        }
        else
            invalid(5);
    }
    else
        invalid(5);

    return;
}

void Exp()
{
    if (id())
    {
        curr++;
        if (str[curr] == '=')
        {
            curr++;
            if (str[curr] == '\'')
            {
                curr++;
                if (str[curr] == 'C')
                {
                    curr++;
                    if (str[curr] == 'h')
                    {
                        curr++;
                        if (str[curr] == 'a')
                        {
                            curr++;
                            if (str[curr] == 'r')
                            {
                                curr++;
                                if (str[curr] == 'a')
                                {
                                    curr++;
                                    if (str[curr] == 'c')
                                    {
                                        curr++;
                                        if (str[curr] == 't')
                                        {
                                            curr++;
                                            if (str[curr] == 'e')
                                            {
                                                curr++;
                                                if (str[curr] = 'r')
                                                {
                                                    curr++;
                                                    if (str[curr] == '\'')
                                                    {
                                                        return;
                                                    }
                                                    else
                                                        invalid(6);
                                                }
                                                else
                                                    invalid(6);
                                            }
                                            else
                                                invalid(6);
                                        }
                                        else
                                            invalid(6);
                                    }
                                    else
                                        invalid(6);
                                }
                                else
                                    invalid(6);
                            }
                            else
                                invalid(6);
                        }
                        else
                            invalid(6);
                    }
                    else
                        invalid(6);
                }
                else
                    invalid(6);
            }
            else
                invalid(6);
        }
        else
            invalid(6);
    }
    else
        invalid(6);
}

int main()
{
    FILE *fp;
    fp = fopen("file.txt", "r");

    // char c = fgetc(fp);
    // int i = 0;
    // while(c != '\0'){
    // 	str[i++] = c;
    // 	c = fgetc(fp);
    // }
    // printf("%s\n", str);

    query();

    valid();

    fclose(fp);
}