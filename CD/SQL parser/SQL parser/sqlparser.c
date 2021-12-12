/* SQL parser 
Query -> select Parameters Fclause Wclause
Parameters -> id Pprime
Pprime->Epsilon | ,Parameters
Fclause -> from Parameters
Wclause -> where Exp
Exp -> id='Character'
*/

#include "sqlla.h"

#include <stdio.h>
#include <stdlib.h>
FILE *f1;
void Query();
void Parameters();
void Pprime();
void Fclause();
void Wclause();
void Exp();
void valid();
void invalid();

struct token tok;
int main()
{
	f1 = fopen("input.c", "r");

	Query();

	valid();
}

void Query()
{
	tok = getNextToken(f1);
	if (strcmp(tok.token_name, "select") == 0)
	{
		printf("Entered after select");
		Parameters();
		Fclause();
		Wclause();
	}
}

void valid()
{
	printf("\n**compilation successful***\n");
}

void invalid()
{

	printf("***error!!!***");
	exit(0);
}

void Parameters()
{
	tok = getNextToken(f1);
	printf("token name is %s", tok.token_name);

	if (strcmp(tok.type, "identifier") == 0)
	{

		tok = getNextToken(f1);
		printf("token name is %s", tok.token_name);

		Pprime();
	}

	else
	{
		printf("Error 1");
		invalid();
	}
}

void Pprime()
{

	if ((strcmp(tok.token_name, ",") == 0))
	{
		printf("token name is %s", tok.token_name);

		Parameters();
	}
	else
	{
		return;
	}
}

void Fclause()
{
	printf("token name is %s", tok.token_name);
	if (strcmp(tok.token_name, "from") == 0)
	{

		Parameters();
	}
	else
	{
		printf("Error 2");
		invalid();
	}
}

void Wclause()
{

	if (strcmp(tok.token_name, "where") == 0)
	{
		tok = getNextToken(f1);
		printf("token name is %s", tok.token_name);

		Exp();
	}
	else
	{
		invalid();
	}
}

void Exp()
{
	printf("token name is !! %s", tok.token_name);

	if (strcmp(tok.type, "identifier") == 0)
	{
		tok = getNextToken(f1);
		printf("token name is %s", tok.token_name);

		if (strcmp(tok.token_name, "=") == 0)
		{
			tok = getNextToken(f1);
			printf("token name is %s", tok.token_name);

			if (strcmp(tok.token_name, "'") == 0)
			{
				tok = getNextToken(f1);
				printf("token name is %s", tok.token_name);

				if (isalpha(tok.token_name[0]))
				{
					tok = getNextToken(f1);
					if (strcmp(tok.token_name, "'") == 0)
					{
						return;
					}

					else
					{
						invalid();
					}
				}
				else
				{
					invalid();
				}
			}
			else
			{
				invalid();
			}
		}
		else
		{
			invalid();
		}
	}
	else
	{
		invalid();
	}
}
