/* sql la code  */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int symind = 0;
int k = 0;
char c;
int row = 1, col = 1;
struct token
{
	int row, col;
	char type[100];
	char token_name[100];
};

struct token tok;

struct st
{
	int size;
	char lex_name[100];
	char dtype[100];
};

struct st symval[10];

char *keywords[] = {"select", "from", "where"};
char spsymbols[] = {':', ',', '.', ';', '\'', '='};
char arithsymbols[] = {'+', '-', '*', '/', '%', '='};

int isspecialsymbol(char c)
{
	int len = 7;
	for (int i = 0; i < len; ++i)
	{
		if (c == spsymbols[i])
			return 1;
	}
	return 0;
}

int iskeyword(char *w)
{
	for (int i = 0; i < 3; ++i)
	{
		if (strcmp(keywords[i], w) == 0)
			return 1;
	}
	return 0;
}
void filltoken(struct token *tok, char *s, int row1, int column, char *type1)
{
	strcpy(tok->token_name, s);
	tok->row = row1;
	tok->col = column;
	strcpy(tok->type, type1);
}

void insertTable(char *lex, char *type)
{
	strcpy(symval[symind].lex_name, lex);

	strcpy(symval[symind].dtype, type);

	symind++;
}

void newLine()
{
	row++;
	col = 1;
}

struct token getNextToken(FILE *fptr)
{

	tok.row = -1;

	tok.col = col;

	int gotnexttoken = 0;

	while ((c = fgetc(fptr)) != EOF && !gotnexttoken)
	{

		if (isspecialsymbol(c))
		{

			char buf[2];
			buf[0] = c;
			buf[1] = '\0';

			filltoken(&tok, buf, row, col, "SpecialSymbol");

			col++;

			gotnexttoken = 1;
		}

		if (isspace(c))
		{
			col++;
		}
		if (c == '\n')
		{
			newLine();
		}

		else if (isalpha(c))
		{
			printf("entering");
			k = 0;

			char buf[30];
			strcmp(buf, " ");
			tok.row = row;
			tok.col = col++;

			while (isalpha(c) && c != EOF)
			{
				buf[k] = c;
				c = fgetc(fptr);
				col++;
				k++;
			}

			buf[k] = '\0';

			strcpy(tok.token_name, "ID");

			if (iskeyword(buf))
			{
				strcpy(tok.token_name, buf);
				strcpy(tok.type, "keyword");
			}
			else
			{
				strcpy(tok.type, "identifier");
			}

			insertTable(buf, tok.type);
			gotnexttoken = 1;

			fseek(fptr, -1, SEEK_CUR);
		}

		else
		{
			col++;
		}
	}
	fseek(fptr, -1, SEEK_CUR);

	return tok;
}
