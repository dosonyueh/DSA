#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Size 500000
#define Size_s 1000
void Input(char*,int *,int*);
int compare(char,char);
void infix_to_postfix(char* , int*, double*);
char incoming_pri[7] = {'#',')','+','-','*','/','('};
char instack_pri[6] = {'#','(','+','-','*','/'};
void calculation(double*);
int main()
{
	int row = 0,i = 0,end = 0;
	int column = 0;
	char* infix;
	double* postfix;
	postfix = (double*)malloc(sizeof(double) * Size);
	while(1)
	{	
		infix = (char*)malloc(sizeof(char) * Size);
		Input(infix,&column,&end);
		if(end == 1)break;
		infix_to_postfix(infix,&column,postfix);
		calculation(postfix);
	}
	return 0;
}
void Input(char* infix,int* column,int* end)
{
	int i = 0;
	if(fgets(infix,Size,stdin) == NULL)
	{
		*end = 1;
		return;
	}
	for(i = 0; i<Size;i++)
	{
		if(infix[i] == '\n')
		{
			*column = i;
			infix[i] = '#';
		}
	}
}

void infix_to_postfix(char* infix,int* column, double* postfix)
{
	//flag用來判斷連續為+,- 可直接輸出
	int top = 0 ,j = 0,flag = 1 ,idx_postfix = 0,num = 0,flag_2 = 0;
		char *stack = (char*)malloc(sizeof(char)*Size_s);
		stack[top] = '#';
		top = 0;idx_postfix = 0;num = 0; flag = 1,flag_2 = 0;
		for(j = 0;j < (*column)+1; j++)
		{
			switch(infix[j])
			{
				case ')'://下個為 ) 則將 ( 之前的堆疊取出
					num = 0;
					while(stack[top] != '(')
					{
						postfix[idx_postfix] = stack[top--];
						idx_postfix++;
					}
					top--;
					break;
				case '#'://下個為 # 則將堆疊全部取出
					num = 0;
					while(stack[top] != '#')
					{
						postfix[idx_postfix] = stack[top--];
						idx_postfix++;
					}
					break;
				case '(':
				case '*':
				case '/':
					num = 0;
					while(compare(stack[top],infix[j]))
					{
						postfix[idx_postfix++] = stack[top--];
						flag = 1;
					}
					stack[++top] = infix[j];
					flag = 1;
					break;
				case '+':
				case '-':
					num = 0;
					if(flag == 1)
					{
						stack[++top] = infix[j];
						flag = 2;
					}
					else
					{
						while(compare(stack[top],infix[j]))
						{
							postfix[idx_postfix++] = stack[top--];
						}
						stack[++top] = infix[j];
						flag = 1;
					}
					break;
				default :
					if(num != 0)
					{
						idx_postfix--;
						postfix[idx_postfix++] = infix[j] + ((postfix[idx_postfix]-48)*10);
						flag_2++;
					}
					else if(num == 0)
						postfix[idx_postfix++] = infix[j];
					if(flag == 2)
					{
						postfix[idx_postfix++] = stack[top--];
					}
					flag = 0;
					num = 1;
				break;
			}
		}
		column -= flag_2;
		free(stack);
}

int compare(char stack,char infix)
{
	int idx_stack = 0, idx_infix = 0;
	while(instack_pri[idx_stack] != stack)
	{idx_stack++;}
	while(incoming_pri[idx_infix] != infix)
	{idx_infix++;}
	infix = idx_stack/2 >= idx_infix/2 ? 1:0 ;
	return infix;
}

void calculation(double* postfix)
{
	int i = 0,j = 0,top = 0,flag = 0;
		double *stack =(double*) malloc(sizeof(double) * Size_s);
		flag = 0;
		j = 0;top = 0;
		while(postfix[j] != 0)
		{
			if(postfix[j] == 43)
			{
				stack[top-2] += stack[top-1];
				top --;flag = 0;
			}
			else if(postfix[j] == 42)
			{
				stack[top-2] *= stack[top-1];
				top --;flag = 0;
			}
			else if(postfix[j] == 45)
			{
				stack[top-2] -= stack[top-1];
				top--;flag = 0;
			}
			else if(postfix[j] == 47)
			{
				stack[top-2] /= stack[top-1];
				top--;flag = 0;
			}
			else
			{	if(flag == 0)
				{
					stack[top++] = postfix[j] -48;
					flag = 0;
				}
				else if(flag == 1)
				{
					top--;
					stack[top] = stack[top]*10+(postfix[j]-48);
					top++;
				}
			}
			j++;
		}
		printf("%.15f\n",stack[top-1]);
		free(stack);
}
