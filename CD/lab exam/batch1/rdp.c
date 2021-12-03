#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include </home/ugcse/Documents/190905136/Lab6/la.c>

FILE *fin;
struct token tkn;

void Start();
void idnum();
void idnumPrime();
void term();
void Fclause();
void Iden();
void IdenPrime();

void Invalid(char ch)
{
	printf("---Error---\n");
	printf("%c\n", ch);
	exit(0);
}

void Valid()
{
	printf("---Success---\n");
	exit(0);
}

void Start()
{
	char x = 's';
	tkn = getNextToken(fin);
	if(strcmp("SUBTRACT", tkn.token_name) == 0)
	{
		idnum();
		Fclause();
	}
	else
		Invalid(x);
}

void idnum()
{
	term();
	idnumPrime();
}

void idnumPrime()
{
	tkn = getNextToken(fin);
	if(strcmp(",", tkn.token_name) == 0)
	{
		idnum();
	}
}

void term()
{
	char x = 't';
	tkn = getNextToken(fin);
	if(strcmp("ID", tkn.token_name) == 0 || strcmp(tkn.type, "Number") == 0)
	{
		return;
	}
	else
		Invalid(x);
}

void Fclause()
{
	char x = 'f';
	//tkn = getNextToken(fin);
	if(strcmp("FROM", tkn.token_name) == 0)
	{
		Iden();
	}
	else 
		Invalid(x);
}

void Iden()
{
	char x ='e';
	tkn = getNextToken(fin);
	if(strcmp("ID", tkn.token_name) == 0)
	{
		IdenPrime();
	}
	else
		Invalid(x);
}

void IdenPrime()
{
	tkn = getNextToken(fin);
	if(strcmp(",", tkn.token_name) == 0)
	{
		Iden();
	}
}

int main()
{
	fin = fopen("input.txt", "r");
	Start();
	Valid();
}

