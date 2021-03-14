#include <stdlib.h>
#include <stdio.h>
#define len 5

void start(int*,int*,int [][4]);
int main()
{
	int col = 0,row = 0,i,j;
	int *m = &row,*n = &col;
	int spec[2*len][4] = {0};
	start(m,n,spec);
/*	printf("輸入遊戲大小:\n");
	scanf("%d %d",&n,&m);
	printf("輸入遊戲條件:\n");
	for (i = 0 ; i < 2*m ;i++)
	{
		scanf("%d %d %d %d",&spec[i][0],&spec[i][1],&spec[i][2],&spec[i][3]);
	}
	printf("遊戲條件為:\n");
	for (i = 0 ; i < 2*row;i++)
	{	
		for(j = 0 ; j < 4 ;j++)
		{
			printf("%d ",spec[i][j]);
		}
		printf("\n");
	}
*/
}

void start(int* m,int* n,int spec[][4])
{
	int i,j;
	printf("輸入遊戲大小:\n");
	scanf("%d %d",m,n);
	printf("輸入遊戲條件:\n");
	for (i = 0 ; i < 2*(*m) ;i++)
	{
		scanf("%d %d %d %d",&spec[i][0],&spec[i][1],&spec[i][2],&spec[i][3]);
	}
	printf("遊戲條件為:\n");
	for (i = 0 ; i < 2*(*m);i++)
	{
		for(j = 0 ; j < 4 ;j++)
		{
			printf("%d ",spec[i][j]);
		}
		printf("\n");
	}
}
