#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Size 100
void Input(char*,int*,int *,char equ[][Size]);
int main()
{
	char input[Size] = {0},equ[][Size] = {0};
	int column[100] = {0};
	int row = 0;
	int i,j;
	Input(input,column,&row,equ);
	for(i = 0 ; i<row;i++)
	{
		for(j = 0;j<column[i];j++)
			printf("%c",equ[i][j]);
		printf("\n");
	}
	printf("row = %d",row);


}

void Input(char input[],int* column,int* row,char equ[][Size])
{
	int i = 0,len,j = 0,k = 0;
	while(scanf("%[^EOF],s",input) != EOF)
	{
		len = strlen(input);
	}
	for(i = 0;i<len;i++)
	{
		equ[j][k] = input[i];
		k++;
		if(input[i] == '\n')
		{
			equ[j][k-1] = '\0';
			column[j] = k;
			(*row)++;
			k = 0;
			j++;

		}
	}
}
