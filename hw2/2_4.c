#include <stdio.h>
#include <stdlib.h>

int ans = 0;
/*
int count = 0;
int arr[100];
int count2 = 0;
int arr2[100];
*/
void search(int** tree,int node,int left,int right)
{
	if(node == 0)
	{
		ans++;
	//	arr[count++] = tree[node][0];
	//	arr2[count2++] = tree[node][0];
		if(tree[node][1] != -1)
			search(tree,tree[node][1]-1,left,tree[node][0]);
		if(tree[node][2] != -1)
			search(tree,tree[node][2]-1,tree[node][0],right);
	}
	else
	{
		if(tree[node][0] >= left && tree[node][0] <= right)
		{
			ans++;
	//		arr[count++] = tree[node][0];
	//		arr2[count2++] = tree[node][0];
			if(tree[node][1] != -1)
				search(tree,tree[node][1]-1,left,tree[node][0]);
			if(tree[node][2] != -1)
				search(tree,tree[node][2]-1,tree[node][0],right);
		}
		else
		{
	//		arr2[count2++] = tree[node][0];
			if(tree[node][1] != -1)
			{
				if( tree[node][0] >= right)
					search(tree,tree[node][1]-1,left,right);
			}
			if(tree[node][2] != -1)
			{
				if( tree[node][0] <= left)
					search(tree,tree[node][2]-1,left,right);
			}
		}

	}
}

int main()
{
	int num_of_node,i;
	char c;
	scanf("%d",&num_of_node);
	while((c = getchar()) != EOF && c != '\n');
	int** tree;
	tree = (int**)malloc(sizeof(int *) * num_of_node);
	for(i = 0 ; i < num_of_node ; i++)
	{
		tree[i] = (int*)malloc(sizeof(int) * 3);
		scanf("%d %d %d",&tree[i][0],&tree[i][1],&tree[i][2]);
		while((c = getchar()) != EOF && c != '\n');
	}
	search(tree,0,1,1000000000);
	printf("%d\n",ans);
}
