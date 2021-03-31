#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Size 1000000
#define N 100000
void Input(char*,int *,int *,char**);
int compare(char,char);
void infix_to_postfix(char** , int*, double*,int);
void Input_to_infix(char [],int* ,int* ,char**);
char incoming_pri[7] = {'#',')','+','-','*','/','('};
char instack_pri[6] = {'#','(','+','-','*','/'};
void calculation(double* ,int*);
int main()
{
	int i = 0,j = 0;
//	char* input = (char*)malloc(sizeof(char) * Size);
	char* input = calloc(Size,sizeof(char));
	int row = 0,max = 0;
	int* column = calloc(Size,sizeof(int));
	char** infix;
	infix = (char**)calloc(N,sizeof(char*));
	for(i = 0 ; i<N;i++)
//		infix[i] = (char*)calloc(Size,sizeof(char));
	while(1)
	{
		char* input = calloc(Size,sizeof(char));
		if(fgets(input,Size,stdin) == NULL)break;
		infix[i] = input;
		for(j = 0;j<Size;i++)
		{
			if(infix[i][j] == '\n')
			{
				infix[i][j] = '#';
				column[i] = j-1;
			}
		}
		double* postfix = calloc(max,sizeof(double));
		infix_to_postfix(infix,column,postfix,i);
		calculation(postfix,column);
	}
//	Input(input,&row,column,infix);

//	int* column = (int*)malloc(sizeof(int) * (row+3));

//	Input_to_infix(input,column,&row,infix);

/*	free(input);
	for(int i = 0 ; i<row ; i++)
	{
		double* postfix = calloc(max,sizeof(double));
		infix_to_postfix(infix,column,postfix,row,i);
		calculation(postfix,column,row);
		free(postfix);
	}
*/
/*	double** postfix;
	postfix = calloc(row+3,sizeof(double*));
	for(int a = 0;a<row+3;a++)
		postfix[a]=calloc(max,sizeof(double));
	
	infix_to_postfix(infix,column,postfix,row);

	for(int a = 0;a<row+3;a++)
		free(infix[a]);
	free(infix);
	
	calculation(postfix,column,row);
	for(int a = 0;a<row+3;a++)
		free(postfix[a]);
	free(postfix);
*/	free(column);
	for(int a = 0;a<N;a++)
		free(infix[a]);
	free(infix);
	
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
void Input(char input[],int* row,int* column , char** infix)
{
	int i = 0,len = 0,j = 0,k = 0;
	while(0)
	{
		if(fgets(input,Size,stdin) == NULL)break;	
		len = strlen(input);
		for(i = 0 ;i<len;i++)
		{
			infix[j][k] = input[i];
			k++;
			if(input[i] == '\n')
			{
				*row++;
				infix[j][k-1] = '#';
				column[j] = k-1;
				k = 0;
				j++;
			}	
		}
	}
//	if(fgets(input,Size,stdin) == NULL)break;
/*	for(i = 0;i<len;i++)
	{
		k++;
		if(input[i] == '\n')
		{//#代表一列的結束
			(*row)++;
			if(k>*max)*max = k;
			k = 0;
			j++;

		}
	}*/
}

void infix_to_postfix(char** infix,int* column, double* postfix,int numofrow)
{
	//flag用來判斷連續為+,- 可直接輸出
	int top = 0,j = 0,flag = 1 ,idx_postfix = 0,num = 0,flag_2 = 0;
		char *stack = calloc(Size,sizeof(char));
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
	int j = 0,top = 0,flag = 0;
		double *stack = calloc(Size,sizeof(double));
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
