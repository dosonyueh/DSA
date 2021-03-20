#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Size 100
void Input(char*,int*,int *,char equ[][Size]);
int compare(char,char);
void infix_to_postfix(char [][Size] , int*, char [][Size]);
char incoming_pri[7] = {'#',')','+','-','*','/','('};
char instack_pri[6] = {'#','(','+','-','*','/'};
int main()
{
	char input[Size] = {0},infix[][Size] = {0};
	int column[100] = {0};
	int row = 0;
	int i,j;
	Input(input,column,&row,infix);
	for(i = 0 ; i<row;i++)
	{
		for(j = 0;j<column[i];j++)
			printf("%c",infix[i][j]);
		printf("\n");
	}
	printf("row = %d",row);


}

void Input(char input[],int* column,int* row,char infix[][Size])
{
	int i = 0,len,j = 0,k = 0;
	while(scanf("%[^EOF],s",input) != EOF)
	{
		len = strlen(input);
	}
	for(i = 0;i<len;i++)
	{
		infix[j][k] = input[i];
		k++;
		if(input[i] == '\n')
		{//#代表一列的結束
			infix[j][k-1] = '#';
			column[j] = k;
			(*row)++;
			k = 0;
			j++;

		}
	}
}

void infix_to_postfix(char infix[][Size],int* column, char postfix[][Size])
{
	//flag用來判斷連續為+,- 可直接輸出
	int top = 0, i = 0 ,j = 0,flag = 1 ,idx_postfix = 0;
	char stack[Size];
	stack[top++] = '#';
	for(j = 0;j < *column ; j++)
	{
		switch(infix[i][j])
		{
			case ')'://下個為 ) 則將 ( 之前的堆疊取出
				while(stack[top] != '(')
				{
					postfix[i][idx_postfix] = stack[top--];
					idx_postfix++;
				}
				break;
			case '#'://下個為 # 則將堆疊全部取出
				while(stack[top] != '#')
				{
					postfix[i][idx_postfix] = stack[top--];
					idx_postfix++;
				}
				break;
			case '(':
			case '*':
			case '/':
				while(compare(stack[top],infix[i][j]))
				{
					postfix[i][idx_postfix] = stack[top--];
					idx_postfix++;
					flag = 1;
				}
				stack[++top] = infix[i][j];
				flag = 1;
				break;
			case '+':
			case '-':
				if(flag == 1)
				{
					stack[++top] = infix[i][j];
					flag = 2;
				}
				else
				{
					while(compare(stack[top],infix[i][j]))
					{
						postfix[i][idx_postfix] = stack[top--];
						idx_postfix++;
					}
					stack[++top] = infix[i][j];
					flag = 1;
				}
				break;
			default :
				postfix[i][idx_postfix++] = infix[i][j];
				if(flag == 2)
				{
					postfix[i][idx_postfix] = stack[top--];
					idx_postfix++;
				}
				flag = 0;
				break;
		}
	}
}

int compare(char stack,char infix)
{
	int idx_stack = 0, idx_infix = 0,ans = 0;
	while(instack_pri[idx_stack] != stack)
		idx_stack++;
	while(incoming_pri[idx_infix] != infix)
		idx_infix++;
	infix = idx_stack/2 >= idx_infix/2 ? 1:0 ;
	return infix;
}
