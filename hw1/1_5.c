#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define Col 100
#define L 20
struct node{
	int cabin;
	struct node *next;
	struct node *before;
	int flag;
};
typedef struct node Node;
void calculation(char*,Node**,Node**);
void enter(int,int,Node**,Node**);
void leave(int,Node**,Node**);
void output(Node**,int);
void migrate(int,int,Node**,Node**);
bool l_s[1000] = {0};//last_reversed
Node *head,*current;
int main()
{
	int i = 0,n = 0 ,k = 0;
	char c;
	scanf("%d %d",&k,&n);
	while ((c = getchar()) != EOF && c != '\n');
	char* input = (char*)calloc(n * L,sizeof(char));
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
{	
	//反轉r_a
	Node *temp;
	temp = h_stack[r_a];
	if(temp == NULL)
		return;
	h_stack[r_a] = t_stack[r_a];
	t_stack[r_a] = temp;
	//r_b->r_a
	if(h_stack[r_b] == NULL)
	{
		h_stack[r_b] = h_stack[r_a];
		t_stack[r_b] = t_stack[r_a];
	}
	else if(l_s[r_b] == 0 && l_s[r_a] == 0)
	{
		t_stack[r_b]->next = h_stack[r_a];
		h_stack[r_a]->next = t_stack[r_b];
		t_stack[r_b] = t_stack[r_a];	
	}
	else if(l_s[r_b] == 0 && l_s[r_a] == 1)
	{
		t_stack[r_b]->next = h_stack[r_a];
		h_stack[r_a]->before = t_stack[r_b];	
		t_stack[r_b] = t_stack[r_a];	
	}
	else if(l_s[r_b] == 1 && l_s[r_a] == 0)
	{
		t_stack[r_b]->before = h_stack[r_a];
		h_stack[r_a]->next = t_stack[r_b];
		t_stack[r_b] = t_stack[r_a];	
	}
	else if(l_s[r_b] == 1 && l_s[r_a] == 1)
	{
		t_stack[r_b]->before = h_stack[r_a];
		h_stack[r_a]->before = t_stack[r_b];
		t_stack[r_b] = t_stack[r_a];	
	}
	if(t_stack[r_b]->next == NULL)
		l_s[r_b] = 0;
	else if(t_stack[r_b]->before == NULL)
		l_s[r_b] = 1;
	h_stack[r_a] = NULL;t_stack[r_a] = NULL;l_s[r_a] = 0;
	


/*	//反轉linked list
	head = h_stack[r_a];
	Node *temp = (Node*)calloc(1,sizeof(Node));
	Node *current = head;
	Node *temp = NULL;
	if(head == NULL)
		return;
	temp = t_stack[r_a];
	t_stack[r_a] = h_stack[r_a];
	h_stack[r_a] = temp;

	while(current != NULL)
	{
		if(current->next == NULL)
			h_stack[r_a] = current;
		temp = current->next;
		current->next = current->before;
		current->before = temp;
		current = temp;
	}

	//反轉後接上
	head = h_stack[r_b];
	if(head == NULL)
	{
		h_stack[r_b] = h_stack[r_a];
		t_stack[r_b] = t_stack[r_a];
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
	h_stack[r_a] = NULL;t_stack[r_a] = NULL;
*/
}


void enter(int rail,int num,Node** h_stack,Node** t_stack )
{
	head = h_stack[rail];
	Node *ptr = (Node*)calloc(1,sizeof(Node));
	Node *current = head;
	ptr->cabin = num;
	ptr->next = NULL;
	ptr->before = NULL;
	ptr->flag = 0;
	if(head == NULL)
	{
		head = ptr;
		l_s[rail] = 0;
		h_stack[rail] = head;
		t_stack[rail] = head;
	}
	else
	{
		if(l_s[rail] == 0)
		{
			current = t_stack[rail];
			current->next = ptr;
			ptr->before = current;
			t_stack[rail] = ptr;
		}
		else if(l_s[rail] == 1)
		{
			current = t_stack[rail];
			current->before = ptr;
			ptr->next = current;
			t_stack[rail] = ptr;
		}
	}
}

void leave(int rail,Node** h_stack,Node** t_stack)
{
	head = h_stack[rail];
	Node *current = t_stack[rail];
	if(current == NULL)
		return ;
	Node *prev = current;
/*	while(current->next != NULL)
	{
		prev = current;
		current = current->next;
	}
*/	
	if(current == head)
	{
		h_stack[rail] = NULL;
		t_stack[rail] = NULL;
		free(current);
		current = NULL;
	}
	else if(l_s[rail] == 0)
	{
		prev = t_stack[rail]->before;
		current = prev->next;
		prev->next = NULL;
		t_stack[rail] = prev;
		free(current);
		current = NULL;
	}
	else if(l_s[rail] == 1)
	{
		prev = t_stack[rail]->next;
		current = prev->before;
		prev->before = NULL;
		t_stack[rail] = prev;
		free(current);
		current = NULL;
	}
}

void output(Node** h_stack,int k)
{
	int i = 0;
	bool flag = 0;
	Node* current,*prev;
	for(i = 0 ; i < k ; i++)
	{
		flag = 0;	
		head = h_stack[i];
		current = head;
		if(h_stack[i] == NULL)
		{
			printf("\n");
			continue;
		}
		while(current != NULL)
		{
			if(head->next == NULL && head->before != NULL)
				head->flag = 1;
			 if(current->next != NULL)
			{
				if(current->next->next != NULL)
				{
					if(current->next->next == current)
						current->next->flag = 1;
				}
			}
			 if(current->before != NULL)
			{
				if(current->before->before != NULL)
				{
					if(current->before->before == current)
						current->before->flag = 1;
				}
			}
			if(current->flag == 1)
				flag = !flag;
			if(flag == 0)
			{
				printf("%d ",current->cabin);
				prev = current;
				current = current->next;
				free(prev);
				prev = NULL;
			}
			else if(flag == 1)
			{
				printf("%d ",current->cabin);
				prev = current;
				current = current->before;
				free(prev);
				prev = NULL;
			}
		}
		printf("\n");
/*		current = head;
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
*/
	}
	
}
