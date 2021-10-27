#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int i,row,col;

struct token
{
	int index;
	unsigned int row,col;
	char token_name[ ];
};

// ++ and -- so not adding + and -
char arithsymbols[] = {'*', '%'};
char spsymbols[] = { ':', ',', '.','?', ';'};
char *keywords[] = { "if", "else","printf", "case", "break", "float","int", "return", "for", "while",
"const", "bool"};


int iskeyword(char *key)
{
	for(i=0;i<12;i++)
	{
		if (strcmp(key, keywords[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int isarithsymbol(char ch)
{
	for(i=0;i<4;i++)
	{
		if(arithsymbols[i]==ch)
		{
			return 1;
		}
	}
	return 0;
}

void newLine()
{
	row++;
	col = 1;
}

int isspsymbol(char ch)
{
	for(i=0;i<5;i++)
	{
		if(spsymbols[i]==ch)
		{
			return 1;
		}
	}
	return 0;
}

void tokeninput(struct token *tok, char c, int row, int col)
{
	tok->token_name[0] = c;
	tok->index =0;
	tok->row = row;
	tok->col = col;
}


struct token getNextToken(FILE *f,char *name)
{
	char c;
	struct token tkn;
	int gotToken = 0;

	while (!gotToken && (c = fgetc(f)) != EOF)
	{
		if (isspsymbol(c)||isarithsymbol(c)){
			tokeninput(&tkn, c, row, col);
			gotToken = 1;
			++col;
		}
		else if (c == '('||c==')'||c=='}'||c=='{'||c==']'||c=='[')
		{
			tokeninput(&tkn, c, row, col);
			gotToken = 1;
			++col;
		}
		else if (c == '+')
		{
			int next = fgetc(f);
			if (next != '+')
			{
				tokeninput(&tkn, c, row, col);
				gotToken = 1;
				++col;
				fseek(f, -1, SEEK_CUR); //shift file pointer back by 1
			}
			else
			{
				tokeninput(&tkn, c, row, col);
				strcpy(tkn.token_name, "++");
				gotToken = 1;
				col += 2; /*skip 2 columns cuz after reading c we read another character too */
			}
		}
		else if (c == '-')
		{
			int next = fgetc(f);
			if (next != '-')
			{
				tokeninput(&tkn, c, row, col);
				gotToken = 1;
				++col;
				fseek(f, -1, SEEK_CUR); //shift file pointer back by 1
			}
			else
			{
				tokeninput(&tkn, c, row, col);
				strcpy(tkn.token_name, "--");
				gotToken = 1;
				col += 2; /*skip 2 columns cuz after reading c we read another character too */
			}
		}
		else if (c == '='){
			int next = fgetc(f);
			if (next != '=')
			{
				tokeninput(&tkn, c, row, col);
				gotToken = 1;
				++col;
				fseek(f, -1, SEEK_CUR); //shift file pointer back by 1
			}
			else
			{
				tokeninput(&tkn, c, row, col);
				strcpy(tkn.token_name, "==");
				gotToken = 1;
				col += 2; /*skip 2 columns cuz after reading c we read another character too */
			}
		}

}