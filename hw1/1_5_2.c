#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Col 100
#define L 20
struct node{
	int cabin;
	struct node *next;
	struct node *before;
	bool flag;
};
typedef struct node Node;
void calculation(char*,Node**,Node**);
void enter(int,int,Node**,Node**);
void leave(int,Node**,Node**);
void output(Node**,int);
void migrate(int,int,Node**,Node**);
Node *head;
int main()
{
	int i = 0,n = 0 ,k = 0;
	char c;
	scanf("%d %d",&k,&n);
	while ((c = getchar()) != EOF && c != '\n');
	char* input = (char*)calloc(L,sizeof(char));
	char* oper = (char*)calloc(L,sizeof(char));
	Node** h_stack = (Node**)calloc(k,sizeof(Node*));
	Node** t_stack = (Node**)calloc(k,sizeof(Node*));
	for(i = 0 ; i < n;i++)
	{
		fgets(input,L,stdin);
		calculation(input,h_stack,t_stack);
	}
	output(h_stack,k);
	free(h_stack);
	return 0;	
}

void calculation(char* oper,Node** h_stack,Node** t_stack)
{
	int j = 0,rail = 0,cabin = 0,c = 0,d = 0,k = 0,r_a = 0,r_b = 0;
	int space[5] = {0};
		rail = 0,cabin = 0,j = 3,k = 0,r_a = 0,r_b = 0;
		switch(oper[0])
		{
			case 'e':
				while(oper[j] != '\n')
				{
					if(oper[j] == ' ')
					{
						space[k] = j;
						k++;
					}
					j++;
				}
				for(c = space[0]+1;c < space[1];c++)
				{
					rail = rail*10 + oper[c] -48;
				}
				for(d = space[1]+1;d < j;d++)
					cabin = cabin*10 + oper[d] -48;
				enter(rail,cabin,h_stack,t_stack);
				break;
			case 'l':
				while(oper[j] != '\n')
				{
					if(oper[j] == ' ')
					{
						space[k] = j;
						k++;
					}
					j++;
				}
				for(c = space[0]+1;c < j;c++)
				{
					rail = rail*10+ oper[c] - 48;
				}
				leave(rail,h_stack,t_stack);
				break;
			case 'm':
				while(oper[j] != '\n')
				{
					if(oper[j] == ' ')
					{
						space[k] = j;
						k++;
					}
					j++;
				}
				for(c = space[0]+1;c<space[1];c++)
					r_a = r_a*10 +oper[c]-48;
				for(d = space[1]+1;d<j;d++)
					r_b = r_b*10+oper[d]-48;
				migrate(r_a,r_b,h_stack,t_stack);
				break;
		}
}

void migrate(int r_a,int r_b,Node** h_stack,Node** t_stack)
{//反轉linked list
	Node *temp = (Node*)malloc(sizeof(Node));
	Node *current;
	if(h_stack[r_a] == NULL)
		return;
	temp = t_stack[r_a];
	t_stack[r_a] = h_stack[r_a];
	h_stack[r_a] = temp;
//反轉後接上
	head = h_stack[r_b];
	if(head == NULL)
	{
		h_stack[r_b] = h_stack[r_a];
		t_stack[r_b] = t_stack[r_a];
		h_stack[r_b]->next = h_stack[r_b]->before;
		h_stack[r_b]->before = NULL;
		t_stack[r_b]->before = t_stack[r_b]->next;
		t_stack[r_b]->next = NULL;
	}
	else
	{
		t_stack[r_b]->next = h_stack[r_a];
		h_stack[r_a]->next = h_stack[r_a]->before;
		h_stack[r_a]->before = t_stack[r_b];
		t_stack[r_a]->before = t_stack[r_a]->next;
		t_stack[r_a]->next = NULL;
		t_stack[r_b] = t_stack[r_a];
	}
	h_stack[r_a] = NULL;t_stack[r_a] = NULL;
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
		current = NULL;
	}
	else
	{
		prev->next = NULL;
		t_stack[rail] = prev;
		free(current);
		current = NULL;
	}
}

void output(Node** h_stack,int k)
{
	int i = 0;
	Node* current,*prev;
	Node* test = h_stack[2];
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
			prev = NULL;
		}
		printf("\n");

	}
}
