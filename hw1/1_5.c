#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Col 20
void Input_spec(int*,int*);
void Input_oper(int*,char**);
void calculate(int*,char**);
void init();

struct node{
	int cabin;
	struct node *next;
	struct node *before;
};
typedef struct node Node;
void enter(Node*,int,int);
void leave(Node*,int);
Node *head = NULL;
int main()
{
	int n = 0 ,k = 0;
	Input_spec(&n,&k);
	char** oper = (char**)malloc(sizeof(char*) * (n+3));
	for(int a = 0; a < n+3;a++)
		oper[a] = (char*)malloc(sizeof(char) * Col);
	Input_oper(&n,oper);
	printf("oper check!\n");
	for(int i = 0 ; i < n;i++)
	{
		for(int j = 0 ; j < Col ;j++)
		{
			printf("%c",oper[i][j]);
		}
		printf("\n");
	}
//	init();
	enter(head,2,2);
	enter(head,3,4);
	//leave(head,1);
	Node* current = head;
	while(current != NULL)
	{	
		printf("%d\n",current->cabin);
		current = current->next;
	}
	
}

void Input_spec(int* n,int* k)
{
	char ch = 0;
	scanf("%d %d",k,n);
	while((ch = getchar()) != EOF && ch != '\n');
}

void Input_oper(int* n,char** oper)
{
	int len , i , j = 0 ,l = 0,num = 0;
	char* input = (char*)malloc(sizeof(char) * Col * (*n));
	while(scanf("%[^EOF],s",input) != EOF)
	{
		len = strlen(input);
		printf("len = %d\n",len);
		printf("n = %d\n",*n);
	}
	for(i = 0 ; i < len ; i++)
	{	
		oper[j][l++] = input[i];
		if(input[i] == '\n')
		{
			printf("j++\n");
			oper[j][l-1] = '\0';
			j++;
			l = 0;
		}
		if(j > *n)
			printf("oper too much\n");
	}
		
}

void init(void)
{
	printf("linked list init\n");
	Node *ptr = (Node*)malloc(sizeof(Node));
	ptr->cabin = 0;
	ptr->next = head;
	ptr->before = head;

}

void calculation(int* n,char** oper)
{
	int i = 0;
	for(i = 0; i <*n;i++)
	{
		
	}
}

void enter(Node *head,int rail,int num)
{
	Node *ptr = (Node*)malloc(sizeof(Node));
	Node *current = head;
	ptr->cabin = num;
	ptr->next = NULL;
	
	if(head == NULL)
		head = ptr;
	else
	{
		while(current->next != NULL)
			current = current->next;
		current->next = ptr;
	}
	printf("%d entered\n",num);
}

void leave(Node *head ,int rail)
{
	Node *current = head;
	while(current->next != NULL)
	{
		current = current->next;
	}
	free(current);
}

