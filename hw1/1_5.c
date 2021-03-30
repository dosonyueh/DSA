#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Col 100
#define Size 10000
void Input_spec(int*,int*);
void Input_oper(int*,char**,int*);

struct node{
	int cabin;
	struct node *next;
	struct node *before;
};
typedef struct node Node;
void calculation(int,char**,Node**,Node**);
void enter(int,int,Node**,Node**);
void leave(int,Node**,Node**);
void output(Node**,int);
void migrate(int,int,Node**,Node**);
Node *head;
int main()
{
	int n = 0 ,k = 0;
	//Input_spec(&n,&k);
	
	char** oper = (char**)calloc(Size,sizeof(char*));
	for(int a = 0; a < Size;a++)
		oper[a] = (char*)calloc(Col,sizeof(char));
	Input_oper(&n,oper,&k);

	Node** h_stack = (Node**)calloc(k,sizeof(Node*));
	Node** t_stack = (Node**)calloc(k,sizeof(Node*));

	calculation(n,oper,h_stack,t_stack);
	output(h_stack,k);
	free(h_stack);
	for(int a = 0 ; a < Size;a++)
		free(oper[a]);
	free(oper);
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
	return 0;	
}

void Input_spec(int* n,int* k)
{
	char ch = 0;
	scanf("%d %d",k,n);
	while((ch = getchar()) != EOF && ch != '\n');
/*	if(scanf("%d %d",k,n)==1)
		while((ch = getchar()) != EOF && ch != '\n');
	else
		printf("enter fail!\n");
*/}

void Input_oper(int* n,char** oper,int* k)
{
	int a,b,len , i , j = 0 ,l = 0,num = 0;
	char* input = (char*)calloc(Col*(Size),sizeof(char));
	while(scanf("%[^EOF],s",input) != EOF)
	{
		len = strlen(input);
	}
	for(i = 0 ; i < len ; i++)
	{
		if(input[i] == ' ')
			a = i;
		if(input[i] == '\n')
		{
			b = i;
			break;
		}
	}
	for(i = 0 ; i < a;i++)
		*k = *k*10+input[i]-48;
	for(i = a+1 ; i < b;i++)
		*n = *n*10+input[i]-48;
	for(i = b+1 ; i < len ; i++)
	{	
		oper[j][l++] = input[i];
		if(input[i] == '\n')
		{
			oper[j][l-1] = '\0';
			j++;
			l = 0;
		}
	}
	free(input);
		
}

void calculation(int n,char** oper,Node** h_stack,Node** t_stack)
{
	int i = 0,j = 0,rail = 0,cabin = 0,c = 0,d = 0,k = 0,r_a = 0,r_b = 0;
	int space[10] = {0};
	for(i = 0; i < n;i++)
	{
		rail = 0,cabin = 0,j = 3,k = 0,r_a = 0,r_b = 0;
		switch(oper[i][0])
		{
			case 'e':
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
				enter(rail,cabin,h_stack,t_stack);
				break;
			case 'l':
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
				leave(rail,h_stack,t_stack);
				break;
			case 'm':
				while(oper[i][j] != '\000')
				{
					if(oper[i][j] == ' ')
					{
						space[k] = j;
						k++;
					}
					j++;
				}
				for(c = space[0]+1;c<space[1];c++)
					r_a = r_a*10 +(int)oper[i][c]-48;
				for(d = space[1]+1;d<j;d++)
					r_b = r_b*10+(int)oper[i][d]-48;
				migrate(r_a,r_b,h_stack,t_stack);
				break;
		}

	}
}

void migrate(int r_a,int r_b,Node** h_stack,Node** t_stack)
{
	head = h_stack[r_a];
	Node *temp = (Node*)calloc(1,sizeof(Node));
	Node *current = head;
	if(head == NULL)
		return;
	t_stack[r_a] = h_stack[r_a];
	while(current != NULL)
	{
		if(current->next == NULL)
			h_stack[r_a] = current;
		temp = current->next;
		current->next = current->before;
		current->before = temp;
		current = temp;
	}

	head = h_stack[r_b];
	if(head == NULL)
	{
		head = h_stack[r_a];
	}
	else
	{
		current = head;
		while(current->next != NULL)
		{
			current = current->next;
		}	
		current->next = h_stack[r_a];
		current->next->before = current;
		t_stack[r_b] = t_stack[r_a];
	}
}


void enter(int rail,int num,Node** h_stack,Node** t_stack )
{
	head = h_stack[rail];
	Node *ptr = (Node*)calloc(1,sizeof(Node));
	Node *current = head;
	ptr->cabin = num;
	ptr->next = NULL;
	ptr->before = NULL;
	if(head == NULL)
	{
		head = ptr;
		h_stack[rail] = head;
		t_stack[rail] = head;
	}
	else
	{
		while(current->next != NULL)
			current = current->next;
		current->next = ptr;
		ptr->before = current;
		t_stack[rail] = ptr;
	}
}

void leave(int rail,Node** h_stack,Node** t_stack)
{
	head = h_stack[rail];
	Node *current = head;
	Node *prev = current;
	if(current == NULL)
		return ;
	while(current->next != NULL)
	{
		prev = current;
		current = current->next;
	}
	if(current == head)
	{
		h_stack[rail] = 0;
		t_stack[rail] = 0;
		free(current);
	}
	else
	{
		prev->next = NULL;
		t_stack[rail] = prev;
		free(current);
	}
}

void output(Node** h_stack,int k)
{
	int i = 0;
	Node* current,*prev;
	for(i = 0 ; i < k ; i++)
	{
		head = h_stack[i];
		current = head;
		prev = current;
		while(current != NULL)
		{	
			printf("%d ",current->cabin);
			prev = current;
			current = current->next;
			free(prev);
		}
		printf("\n");

	}
}
