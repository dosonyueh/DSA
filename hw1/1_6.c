#include <stdlib.h>
#include <stdio.h>

#define NumofNode 1000
struct node{
	int seq[5];
	int num;
	struct node *next;
	struct node *before;
};
typedef struct node Node;

int num[NumofNode];
Node** stack[NumofNode];

Node* new_node(Node** l_node,int* s,int in_th,int n)
{
	Node* ptr = (Node*)malloc(sizeof(Node));
	for(int i = 0;i<n;i++)
		ptr->seq[i] = s[in_th+i];
	ptr->num = n;
	if(l_node != NULL)
		ptr->before = l_node;
	else
		ptr->before = NULL;
	return ptr;
}

void init(int* initial,int n)
{
	int in_th = 0,number = 0,numofnode = 0;
	Node* ptr = (Node*)malloc(sizeof(Node));
	numofnode = ((n-1)/5)+1;
	for(int i = 0;i<numofnode;i++)
	{
		if(n >= 5){
			num[i] = 5;
			n = n-5;
		}else{
			num[i] = n;
		}
	}
	for(int i = 0;i<numofnode;i++)
	{
		
		ptr = new_node(ptr,initial,i*5,num[i]);	
	}
}

int main()
{
	int i = 0,n = 0,q = 0 ,a = 0;
	char c;
	scanf("%d %d",&n,&q);
	while((c = getchar()) != EOF && c != '\n');
	int* initial = (int*)malloc(sizeof(int) * n);
	char* oper = (char*)malloc(sizeof(char) * q);
	for(i = 0 ; i < n; i++)
	{
		scanf("%d",&initial[i]);
	}
	init(initial,n);
	//for(i = 0;i<q;i++)
	//{
	//	fgets(oper,50,stdin);
	//}

}
