#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Size 1000000
void Input(char**,int *,int *);
int compare(char,char);
void infix_to_postfix(char** , int*, double*,int);
void Input_to_infix(char [],int* ,int* ,char**);
char incoming_pri[7] = {'#',')','+','-','*','/','('};
char instack_pri[6] = {'#','(','+','-','*','/'};
void calculation(double*,int*);
int main()
{
//	char* input = (char*)malloc(sizeof(char) * Size);
	int row = 0,i = 0;
//	Input(input,&row);

	int* column = (int*)malloc(sizeof(int) * Size);
	char** infix;
	infix = (char**)malloc(sizeof(char*) * Size);
//	for(int a = 0;a<Size;a++)
//		infix[a]=(char*)malloc(Size * sizeof(char));
	Input(infix,&row,column);
//	int* column = (int*)malloc(sizeof(int) * (row+3));
//	Input_to_infix(input,column,&row,infix);

//	free(input);

	double* postfix;
	postfix = (double*)malloc(sizeof(double) * Size);
	for(i = 0;i<row;i++)
	{
		infix_to_postfix(infix,column,postfix,i);
//	for(int a = 0;a<row+3;a++)
//		free(infix[a]);
//	free(infix);
		calculation(postfix,column);
//	for(int a = 0;a<row+3;a++)
//		free(postfix[a]);
//	free(postfix);
//	}
	}
	free(column);
	
	return 0;
}
void Input_to_infix(char input[],int* column,int* row ,char** infix)
{
	int i = 0,j = 0,k = 0,len = strlen(input);
	for(i = 0 ; i< len ; i++)
	{
		infix[j][k] = input[i];
		k++;
		if(input[i] == '\n')
		{
			infix[j][k-1] = '#';
			column[j] = k-1;
			k = 0;
			j++;
		}
	}
	
}
void Input(char** infix,int* row,int* column)
{
	int i = 0,len = 0,j = 0,k = 0,idx = 0;
	while(1)
	{
		char *str = malloc(sizeof(char) * Size);
		if(fgets(str,Size,stdin) == NULL)break;
		infix[idx] = malloc(sizeof(char) * Size);
		infix[idx] = str;
		for(i = 0; i<Size;i++)
		{
			if(infix[idx][i] == '\n')
			{
				column[idx] = i;
				infix[idx][i] = '#';
				(*row)++;
			}
		}
		idx++;
	}
/*	while(scanf("%[^EOF],s",input) != EOF)
	{	
		len = strlen(input);
	}
	for(i = 0;i<len;i++)
	{
		k++;
		if(input[i] == '\n')
		{//#代表一列的結束
			(*row)++;
			k = 0;
			j++;

		}
	}*/
}

void infix_to_postfix(char** infix,int* column, double* postfix,int numofrow)
{
	//flag用來判斷連續為+,- 可直接輸出
	int top = 0, i = 0 ,j = 0,flag = 1 ,idx_postfix = 0,num = 0,flag_2 = 0;
//	for(i = 0;i < row ; i++){
		char *stack = (char*)malloc(sizeof(char)*Size);
		stack[top] = '#';
		top = 0;idx_postfix = 0;num = 0; flag = 1,flag_2 = 0;
		for(j = 0;j < column[numofrow]+1 ; j++)
		{
			switch(infix[numofrow][j])
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
					while(compare(stack[top],infix[numofrow][j]))
					{
						postfix[idx_postfix] = stack[top--];
						idx_postfix++;
						flag = 1;
					}
					stack[++top] = infix[numofrow][j];
					flag = 1;
					break;
				case '+':
				case '-':
					num = 0;
					if(flag == 1)
					{
						stack[++top] = infix[numofrow][j];
						flag = 2;
					}
					else
					{
						while(compare(stack[top],infix[numofrow][j]))
						{
							postfix[idx_postfix] = stack[top--];
							idx_postfix++;
						}
						stack[++top] = infix[numofrow][j];
						flag = 1;
					}
					break;
				default :
					if(num != 0)
					{
						idx_postfix--;
						postfix[idx_postfix] = infix[numofrow][j] + ((postfix[idx_postfix]-48)*10);
						idx_postfix++;
						flag_2++;
					}
					else if(num == 0)
						postfix[idx_postfix++] = infix[numofrow][j];
					if(flag == 2)
					{
						postfix[idx_postfix] = stack[top--];
						idx_postfix++;
					}
					flag = 0;
					num = 1;
				break;
			}
		}
		column[numofrow] -= flag_2;
		free(stack);
//	}
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

void calculation(double* postfix,int* column)
{
	int i = 0,j = 0,top = 0,flag = 0;
//	for(i = 0 ; i<row ; i++)
//	{
		double *stack =(double*) malloc(sizeof(double) * Size);
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
//	}

}
