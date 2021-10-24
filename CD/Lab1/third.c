#include <stdio.h>
#include <stdlib.h>

int main(){

	FILE *fptr1,*fptr2,*res;

	char c,c1,c2;
	char filename[100];

	printf("Enter the first filename to open for reading: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");

	// Open one file for reading
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}

	printf("Enter the second filename to open for reading \n");
	scanf("%s", filename);
	fptr2 = fopen(filename, "r");

	// Open one file for reading
	if (fptr2 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}

	printf("Enter the filename to open for writing: \n");
	scanf("%s", filename);
	res = fopen(filename, "w+"); // Open another file for writing


	c1=fgetc(fptr1);
	c2=fgetc(fptr2);

	int toggle=0;

	while(c1!=EOF && c2!=EOF){
		if(toggle==0){
			c=c1;
			c1=fgetc(fptr1);
			if(c1=='\n'){
				toggle=1;
			}
		}
		else{
			c=c2;
			c2=fgetc(fptr2);
			if(c2=='\n'){
				toggle=0;
			}
		}
		fputc(c,res);
	}

	while(c1!=EOF){
		fputc(c1,res);
		c1=fgetc(fptr1);
	}
	while(c2!=EOF){
		fputc(c2,res);
		c2=fgetc(fptr2);		
	}

	return 0;

}