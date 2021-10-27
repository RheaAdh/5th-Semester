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

	printf("Enter the filename to open for writing: \n");
	scanf("%s", filename);
	fptr2 = fopen(filename, "w+"); // Open another file for writing

	//Store in arr
	char arr[100];
	int i=0;

	c = fgetc(fptr1);

	// Read contents from file
	while (c != EOF)
	{
		arr[i++]=c;
		c = fgetc(fptr1);
	}

	for(int j=i-1;j>=0;j--){
		c=arr[j];
		fputc(c,fptr2);
	}

	printf("\nContents copied to %s in reverse order\n", filename);

	long int res = ftell(fptr1);

	printf("Size of the file is %ld bytes \n", res);

	fclose(fptr1);
	fclose(fptr2);

	return 0;
}