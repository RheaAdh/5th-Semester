#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main()
{
	char keys[10][20] = {"if","else","while","int","char","float","do","printf","scanf","for"};
	char buffer[100];
	FILE *f1;
	int c1,bufferCounter = 0;
	f1 = fopen("input.c","r");
	if(f1 == NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}
	c1 = getc(f1);
	while(c1 != EOF)
	{
		if(isalpha(c1))
		{
			buffer[bufferCounter++] = c1;
		}
		else
		{
			buffer[bufferCounter] = '\0';
			bufferCounter = 0;
			for(int i = 0 ; i < 10 ; i++)
			{
				if(strcmp(keys[i],buffer) == 0)
				{
					int j = 0;
					while(buffer[j])
					{
						putchar(toupper(buffer[j]));
						j++;
					}
					printf("\n");
					break;
				}
			}
		}
		c1 = getc(f1);
	}
	fclose(f1);
	return 0;
}