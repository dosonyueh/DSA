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
/*	for(i = 0 ; i<row;i++)
	{
		for(j = 0;j<length[i];j++)
			printf("%c",input[i][j]);
		printf("\n");
	}
	printf("\n");
*/}

void Input(char input[][Size],int* length,int* row)
{
	int i = 0;
/*	while(scanf("%s",input[i]) != EOF)
	{
//		scanf("%s",input);
		printf("i = %d\n",i);
		length[i] = strlen(input[i]);
		for(i = 0 ; i<length[0];i++)
			printf("input = %c",input[0][i]);
		printf("last = %c\n",input[0][length[0]]);
		if(input[0][length[0]] == '\0')
			printf("end\n");
		printf("strlen = %d\n",length[0]);
		i++;
	}
*/	
//	scanf("%s",input[i]);
	while(fgets(input[i],100,stdin) != NULL){
		length[i] = strlen(input[i]);
		printf("length = %d\n",length[i]);
		for(int j = 0;j<length[0];j++)
			printf("input = %c",input[0][j]);
	}
}
