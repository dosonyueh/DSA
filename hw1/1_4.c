#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Size 100
void Input(char input[][Size],int*,int *);
int main()
{
	char input[][Size] = {0};
	int length[100] = {0};
	int row = 0;
	int i,j;
	Input(input,length,&row);
	for(i = 0 ; i<row;i++)
	{
		for(j = 0;j<length[i];j++)
			printf("%c",input[i][j]);
		printf("\n");
	}
	printf("\n");
}

void Input(char input[][Size],int* length,int* row)
{
	int i = 0;
	while(scanf("%s",input[i]) != EOF)
	{
//		scanf("%s",input);
		printf("strlen = %ld\n",strlen(input[i]));
		printf("i = %d\n",i);
		length[i] = strlen(input[i]);
		printf("last = %c\n",input[i][length[i-2]]);
		i++;
	}
}

