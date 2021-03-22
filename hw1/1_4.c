#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Size 10000
//void Input(char*,int*,int *,char equ[][Size]);
void Input(char*,int*,int *,char** infix);
int compare(char,char);
void infix_to_postfix(char** , int*, double**,int);
char incoming_pri[7] = {'#',')','+','-','*','/','('};
char instack_pri[6] = {'#','(','+','-','*','/'};
void calculation(double**,int*,int);
int main()
{
	char input[Size] = {0};
	char** infix;
	infix = (char**)malloc(sizeof(char*) * Size);
	for(int a = 0;a<Size;a++)
		infix[a]=(char*)malloc(Size * sizeof(char*));
	int column[Size] = {0};
	int row = 0;
	int i,j;
	Input(input,column,&row,infix);
	double** postfix;
	postfix = (double**)malloc(sizeof(double*) * Size);
	for(int a = 0;a<Size;a++)
		postfix[a]=(double*)malloc(Size *sizeof(double*));
	infix_to_postfix(infix,column,postfix,row);
	free(infix);
	calculation(postfix,column,row);

}

void Input(char input[],int* column,int* row,char** infix)
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
			column[j] = k-1;
			(*row)++;
			k = 0;
			j++;

		}
	}
}

void infix_to_postfix(char** infix,int* column, double** postfix,int row)
{
	//flag用來判斷連續為+,- 可直接輸出
	int top = 0, i = 0 ,j = 0,flag = 1 ,idx_postfix = 0,num = 0,flag_2 = 0;
	for(i = 0;i < row ; i++){
		char *stack = malloc(sizeof(char)*Size);
		stack[top] = '#';
		top = 0;idx_postfix = 0;num = 0; flag = 1,flag_2 = 0;
		for(j = 0;j < column[i]+1 ; j++)
		{
			switch(infix[i][j])
			{
				case ')'://下個為 ) 則將 ( 之前的堆疊取出
					num = 0;
					while(stack[top] != '(')
					{
						postfix[i][idx_postfix] = stack[top--];
						idx_postfix++;
					}
					top--;
					break;
				case '#'://下個為 # 則將堆疊全部取出
					num = 0;
					while(stack[top] != '#')
					{
						postfix[i][idx_postfix] = stack[top--];
						idx_postfix++;
					}
					break;
				case '(':
				case '*':
				case '/':
					num = 0;
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
					num = 0;
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
					if(num != 0)
					{
						idx_postfix--;
						postfix[i][idx_postfix] = infix[i][j] + ((postfix[i][idx_postfix]-48)*10);
						idx_postfix++;
						flag_2++;
					}
					else if(num == 0)
						postfix[i][idx_postfix++] = infix[i][j];
					if(flag == 2)
					{
						postfix[i][idx_postfix] = stack[top--];
						idx_postfix++;
					}
					flag = 0;
					num = 1;
				break;
			}
		}
		column[i] -= flag_2;
		free(stack);
	}
}

int compare(char stack,char infix)
{
	int idx_stack = 0, idx_infix = 0,ans = 0;
	while(instack_pri[idx_stack] != stack)
	{idx_stack++;}
	while(incoming_pri[idx_infix] != infix)
	{idx_infix++;}
	infix = idx_stack/2 >= idx_infix/2 ? 1:0 ;
	return infix;
}

void calculation(double** postfix,int* column,int row)
{
	int i = 0,j = 0,top = 0,flag = 0;
	for(i = 0 ; i<row ; i++)
	{
		double *stack = malloc(sizeof(double) * Size);
		flag = 0;
		j = 0;top = 0;
		while(postfix[i][j] != 0)
		{
			if(postfix[i][j] == 43)
			{
				stack[top-2] += stack[top-1];
				top --;flag = 0;
			}
			else if(postfix[i][j] == 42)
			{
				stack[top-2] *= stack[top-1];
				top --;flag = 0;
			}
			else if(postfix[i][j] == 45)
			{
				stack[top-2] -= stack[top-1];
				top--;flag = 0;
			}
			else if(postfix[i][j] == 47)
			{
				stack[top-2] /= stack[top-1];
				top--;flag = 0;
			}
			else
			{	if(flag == 0)
				{
					stack[top++] = postfix[i][j] -48;
					flag = 0;
				}
				else if(flag == 1)
				{
					stack[--top] = stack[top]*10+(postfix[i][j]-48);
					top++;
				}
			}
			j++;
		}
		printf("%f\n",stack[top-1]);
		free(stack);
	}

}
