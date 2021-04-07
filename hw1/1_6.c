#include <stdlib.h>
#include <stdio.h>

#define NumofNode 1000
struct node{
	int element;
	struct node *next;
	struct node *before;
};
typedef struct node Node;
struct upper_node{
	struct upper_node *next;
	struct upper_node *before;
	int num;
	Node* first_node;
};
typedef struct upper_node U_Node;

int number[NumofNode] = {0};

void Query(int start,int end,int size,U_Node** u_stack)
{
	int start_node = 0,end_node = 0,i = 0,num = 0;
	int* seq = (int*)malloc(sizeof(int) * (end-start+1));
	while(num < start)
		num += number[start_node++];
	start_node--;
	num -= number[start_node];//此時num為第幾個數字
	start -= num;
	end -= num;
	//end_node = start_node;
	//while(num < end)
	//	num += number[end_node++];
	//end_node--;
	Node* current = (Node*)malloc(sizeof(Node));
	current = u_stack[start_node]->first_node;
	for(i = 0;i<start-1;i++)
		current = current->next;
	for(i = 0;i<(end-start+1);i++)
	{
		seq[i] = current->element;
		current = current->next;
	}
}

void init(int* initial,int n,Node** n_stack,int* numofnode,U_Node** u_stack)
{
	int i,j = 0;
	U_Node *u_ptr = (U_Node*)malloc(sizeof(U_Node));
	U_Node *u_current = (U_Node*)malloc(sizeof(U_Node));
	Node *current = (Node*)malloc(sizeof(Node));
	for(i = 0;i<n;i++)
	{
		Node *ptr = (Node*)malloc(sizeof(Node));
		ptr->element = initial[i];
		if(i == 0)
			ptr->before = NULL;
		else
		{
			current->next = ptr;
			ptr->before = current;
		}
		current = ptr;
		if(i % 5 == 0)
		{	
			U_Node *u_ptr = (U_Node*)malloc(sizeof(U_Node));
			u_ptr->first_node = ptr;
			u_ptr->num = 0;
			if(j == 0)
				u_ptr->before = NULL;
			else
			{
				u_ptr->before = u_current;
				u_current->next = u_ptr;
			}
			u_current = u_ptr;
			u_stack[j] = u_ptr; 
			j++;
		}
		//(u_ptr->num) = u_ptr->num +1;
		(u_stack[j-1]->num)++;
	}
	for(i = 0;i<j;i++)
		number[i] = u_stack[i]->num;
}

int main()
{
	int i = 0,n = 0,q = 0 ,a = 0,numofnode = 0;
	char c;
	scanf("%d %d",&n,&q);
	while((c = getchar()) != EOF && c != '\n');
	int* initial = (int*)malloc(sizeof(int) * n);
	char* oper = (char*)malloc(sizeof(char) * q);
	Node** n_stack = (Node**)malloc(sizeof(Node*) * NumofNode);
       	U_Node** u_stack = (U_Node**)malloc(sizeof(U_Node*) * NumofNode);	
	for(i = 0 ; i < n; i++)
	{
		scanf("%d",&initial[i]);
	}
	init(initial,n,n_stack,&numofnode,u_stack);
	Query(4,11,1,u_stack);
/*	for(i = 0;i<q;i++)
	{
		fgets(oper,50,stdin);
	}
*/
}
