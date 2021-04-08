#include <stdlib.h>
#include <stdio.h>

#define NumofNode 50000
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
int ans[50000] = {0};
int numofans = 0;
void merge(int* seq,int l,int m,int r)
{
	int i,j,k;
	int num1 = m - l +1;
	int num2 = r - m;
	int left[num1],right[num2];

	for(i = 0;i < num1;i++)
		left[i] = seq[l+i];
	for(j = 0;j < num2;j++)
		right[j] = seq[m+1+j];
	i = 0;j = 0;k = l;
	
	while(i < num1 && j < num2)
	{
		if(left[i] <= right[j])
			seq[k++] = left[i++];
		else 
			seq[k++] = right[j++];
	}
	while(i < num1)
		seq[k++] = left[i++];
	while(j < num2)
		seq[k++] = right[j++];		
}

void merge_sort(int* seq, int l,int r)
{
	if(l < r)
	{
		int m = (l+r)/2;
		merge_sort(seq,l,m);
		merge_sort(seq,m+1,r);

		merge(seq,l,m,r);
	}
}


void Query(int start,int end,int n,U_Node** u_stack)
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
	merge_sort(seq,0,(end-start));
	ans[numofans++] = seq[n-1];
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

void calculation(char* oper,U_Node** u_stack)
{
	int i = 0,a = 0,b = 0,c = 0,k = 0;
	int start = 0,end = 0,numth = 0;
	int space[5] = {0};
	switch(oper[0])
	{
		case 'Q':
			while(oper[i] != '\n')
			{
				if(oper[i] == ' ')
					space[k++] = i;
				i++;
			}
			space[3] = i;
			for(a = space[0]+1;a < space[1];a++)
				start = start*10 + oper[a] - 48;
			for(b = space[1]+1;b < space[2];b++)
				end = end*10 + oper[b] - 48;
			for(c = space[2]+1;c < space[3];c++)
				numth = numth*10 + oper[c] - 48;
			Query(start,end,numth,u_stack);
			break;

	}
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
	while((c = getchar()) != EOF && c != '\n');
	init(initial,n,n_stack,&numofnode,u_stack);
	for(i = 0;i<q;i++)
	{
		fgets(oper,50,stdin);
		calculation(oper,u_stack);
	}
	for(i = 0;i<numofans;i++)
		printf("%d\n",ans[i]);

}
