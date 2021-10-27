#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fptr1, *fptr2;

	char filename[100], c;

	printf("Enter the filename to open for reading: \n");
	scanf("%s", filename);

	fptr1 = fopen(filename, "r");

	// Open one file for reading
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	
	c = fgetc(fptr1);
	// printf("%c\n",c);

	int lines=1,characters=1;

	// Read contents from file
	while (c != EOF)
	{
		c = fgetc(fptr1);
		// printf("%c\n",c);

		if(c=='\n'){
			lines++;
		}

		if(c!=EOF && c!='\n')
			characters++;
		
	}

	printf("\nTotal no.of lines=  %d and characters= %d.\n", lines,characters);
	fclose(fptr1);

	return 0;
}