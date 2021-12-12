
int main()
{

	FILE *f1 = fopen("input.c", "r");
	int i;

	struct token token1;
	while ((token1 = getNextToken(f1)).row != -1)
	{

		printf("<%s,%d,%d,%s>\n", token1.token_name, token1.row, token1.col, token1.type);
	}
	printf("SYMBOL          TYPE \n");
	printf("-------------------------\n");
	for (i = 0; i < symind; i++)
	{
		printf("%s               %s \n", symval[i].lex_name, symval[i].dtype);
	}
	return 0;
}
