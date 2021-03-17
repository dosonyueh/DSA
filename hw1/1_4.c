#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Size 100
void Input(char*,int*);
int main()
{
	char input[Size] = {0};
	int length = 0;
	int i;
	Input(input,&length);
	for(i = 0 ; i<length;i++)
		printf("%c",input[i]);
	printf("\n");
}

void Input(char* input,int* length)
{
	scanf("%s",input);
	printf("strlen = %ld\n",strlen(input));
	*length = strlen(input);
}

