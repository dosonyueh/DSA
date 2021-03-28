#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Col 100
void Input_spec(int*,int*);
void Input_oper(int*,char**);

struct node{
	int cabin;
	struct node *next;
	struct node *before;
};
typedef struct node Node;
void calculation(int,char**,Node**);
void enter(int,int,Node**);
void leave(int,Node**);
Node *head;
int main()
{
	int n = 0 ,k = 0;
	Input_spec(&n,&k);
	
	Node** h_stack = (Node**)malloc(sizeof(Node*) * k);
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
	calculation(n,oper,h_stack);
/*	enter(2,2,h_stack);
	enter(3,4,h_stack);
	enter(3,4,h_stack);
	leave(2,h_stack);
	Node* current = h_stack[12];
	while(current != NULL)
	{	
		printf("%d\n",current->cabin);
		current = current->next;
	}
*/	
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

void calculation(int n,char** oper,Node** h_stack)
{
	int i = 0,j = 0,rail = 0,cabin = 0,c = 0,d = 0,k = 0;
	int space[10] = {0};
	for(i = 0; i < n;i++)
	{
		rail = 0,cabin = 0,j = 3,k = 0;
		switch(oper[i][0])
		{
			case 'e':
				printf("enter!\n");
				while(oper[i][j] != '\000')
				{
					if(oper[i][j] == ' ')
					{
						space[k] = j;
						k++;
					}
					j++;
				}
				for(c = space[0]+1;c < space[1];c++)
				{
					rail = rail*10 + (int)oper[i][c] -48;
				}
				for(d = space[1]+1;d < j;d++)
					cabin = cabin*10 + (int)oper[i][d] -48;
				enter(rail,cabin,h_stack);
				break;
			case 'l':
				printf("leave!\n");
				while(oper[i][j] != '\000')
				{
					if(oper[i][j] == ' ')
					{
						space[k] = j;
						k++;
					}
					j++;
				}
				for(c = space[0]+1;c < j;c++)
				{
					rail = rail*10+ (int)oper[i][c] - 48;
				}
				leave(rail,h_stack);
				break;
			case 'm':
				break;
		}

	}
}

void enter(int rail,int num,Node** h_stack )
{
	head = h_stack[rail];
	Node *ptr = (Node*)malloc(sizeof(Node));
	Node *current = head;
	ptr->cabin = num;
	ptr->next = NULL;
	if(head == NULL)
	{
		head = ptr;
		h_stack[rail] = head;
		printf("new head establish\n");
	}
	else
	{
		while(current->next != NULL)
			current = current->next;
		current->next = ptr;
	}
	printf("%d entered\n",num);
}

void leave(int rail,Node** h_stack)
{
	head = h_stack[rail];
	Node *current = head;
	Node *prev = current;
	while(current->next != NULL)
	{
		prev = current;
		current = current->next;
	}
	if(current == head)
	{
		h_stack[rail] = 0;
	}
	else
	{
		prev->next = NULL;
		free(current);
	}
}

