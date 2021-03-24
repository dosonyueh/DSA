#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Col 20
void Input_spec(int*,int*);
void Input_oper(int*,int*,char**);

struct node{
int cabin;
struct node *next;
struct node *before;
};
	


int main()
{
	int *n,*k;
	Input_spec(n,k);
	
	char** oper = (char**)malloc(sizeof(char*) * (*n));
	for(int a = 0; a < *n;a++)
		oper[a] = (char*)malloc(sizeof(char) * Col);

	Input_oper(n,k,oper);
	for(int i = 0 ; i < *n;i++)
	{
		for(int j = 0 ; j < Col ;j++)
		{
			printf("%c",oper[i][j]);
		}
		printf("\n");
	}
}

void Input_spec(int* n,int* k)
{
	scanf("%d %d",k,n);
}

void Input_oper(int* n,int* k,char** oper)
{
	int len , i , j = 0 , l = 0;
	char* input = (char*)malloc(sizeof(char) * (*n) * Col);
	while(scanf("%[^EOF],s",input) != EOF)
	{
		len = strlen(input);
	}
	for(i = 0 ; i < len ; i++)
	{
		oper[j][l++] = input[i];
		if(input[i] == '\n');
		{
			j++;
			l = 0;
		}
	}
		
}
