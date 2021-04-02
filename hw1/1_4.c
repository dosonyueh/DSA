#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Size 80000
#define Size_s 10000
//void Input(char*,int *,int*);
int compare(char,char);
int pri(char);
void infix_to_postfix(char* , int*, double*);
char incoming_pri[7] = {'#',')','+','-','*','/','('};
char instack_pri[6] = {'#','(','+','-','*','/'};
char stack_c[Size_s] = {0};
double stack_d[Size_s] = {0};
void calculation(double*);
int main()
{
	int row = 0,i = 0,end = 0;
	int column = 0;
	char* infix;
//	infix = (char*)malloc(sizeof(char) * Size);
//	Input(infix,&row,column);
	double* postfix;
	postfix = (double*)malloc(sizeof(double) * Size);
	infix = (char*)malloc(sizeof(char) * Size);
	//char* str;
	while(1)
	{
		memset(infix,0,Size);
		memset(postfix,0,Size);	
		//if(Input(infix,&column) == 1)break;
		//
		if(fgets(infix,Size,stdin) == NULL)
			end = 1;
		column = strlen(infix)-1;
		infix[column] = '#';
		//Input(infix,&column,&end);
		if(end == 1)break;
		//char *str = malloc(sizeof(char)*Size);
		//if(fgets(str,Size,stdin)==NULL)break;
		infix_to_postfix(infix,&column,postfix);
		calculation(postfix);
	}
	return 0;
}
/*void Input(char* infix,int* column,int* end)
{
	int i = 0;
	//char *str = malloc(sizeof(char) * Size);
	if(fgets(infix,Size,stdin) == NULL)
	{
		*end = 1;
		return;
	}
	//infix = str;
	for(i = 0; i<Size;i++)
	{
		if(infix[i] == '\n')
		{
			*column = i;
			infix[i] = '#';
		}
	}
}
*/
void infix_to_postfix(char* infix,int* column, double* postfix)
{
	//flag用來判斷連續為+,- 可直接輸出
	int top = 0 ,j = 0,idx_postfix = 0,num = 0,flag_2 = 0;
//		char *stack = (char*)malloc(sizeof(char)*Size_s);
		stack_c[top] = '#';
		for(j = 0;j < (*column)+1; j++)
		{
			switch(infix[j])
			{
				case ')'://下個為 ) 則將 ( 之前的堆疊取出
					num = 0;
					while(stack_c[top] != '(')
					{
						postfix[idx_postfix++] = stack_c[top--];
					}
					top--;
					break;
				case '#'://下個為 # 則將堆疊全部取出
					num = 0;
					while(stack_c[top] != '#')
					{
						postfix[idx_postfix] = stack_c[top--];
						idx_postfix++;
					}
					break;
				case '(':
					stack_c[++top] = infix[j];
					num = 0;
					break;
				case '*':
				case '/':
					num = 0;
				//	while(pri(stack_c[top])>=pri(infix[j]))
					while(compare(stack_c[top],infix[j]))
					{
						postfix[idx_postfix++] = stack_c[top--];
						//idx_postfix++;
					}
					stack_c[++top] = infix[j];
					break;
				case '+':
				case '-':
					num = 0;
				/*	if(flag == 1)
					{
						stack_c[++top] = infix[j];
						flag = 2;
					}
					else
				*/	{
				//		while(pri(stack_c[top])>=pri(infix[j]))
						while(compare(stack_c[top],infix[j]))
						{
							postfix[idx_postfix++] = stack_c[top--];
							//idx_postfix++;
						}
						stack_c[++top] = infix[j];
					}
					break;
				default :
					if(num != 0)
					{
						idx_postfix--;
						postfix[idx_postfix++] = infix[j] + ((postfix[idx_postfix]-48)*10);
						//idx_postfix++;
						flag_2++;
					}
					else if(num == 0)
						postfix[idx_postfix++] = infix[j];
				/*	if(flag == 2)
					{
						postfix[idx_postfix++] = stack_c[top--];
						//idx_postfix++;
					}
					flag = 0;
				*/	num = 1;
				break;
			}
		}
		column -= flag_2;
		memset(stack_c,0,Size_s);
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
int pri(char oper)
{
	switch(oper)
	{
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return 2;
		case '/':
			return 2;
		case '#':
			return 0;
		case '(':
			return 0;
	}
}

void calculation(double* postfix)
{
	int j = 0,top = 0,flag = 0;
//		double *stack =(double*) malloc(sizeof(double) * Size_s);
		while(postfix[j] != 0)
		{
			if(postfix[j] == 43)
			{	
				top--;
				stack_d[top-1] += stack_d[top];
				flag = 0;
			}
			else if(postfix[j] == 42)
			{
				top--;
				stack_d[top-1] *= stack_d[top];
				flag = 0;
			}
			else if(postfix[j] == 45)
			{
				top--;
				stack_d[top-1] -= stack_d[top];
				flag = 0;
			}
			else if(postfix[j] == 47)
			{
				top--;
				stack_d[top-1] /= stack_d[top];
				flag = 0;
			}
			else
			{	if(flag == 0)
				{
					stack_d[top++] = postfix[j] -48;
					flag = 0;
				}
				else if(flag == 1)
				{
					
					stack_d[--top] = stack_d[top]*10+(postfix[j]-48);
					top++;
				}
			}
			j++;
		}
		printf("%.15f\n",stack_d[top-1]);
		memset(stack_d,0,Size_s);
}
