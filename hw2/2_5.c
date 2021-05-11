#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

int n,*p,*q,*r,MAX;
void move()
{
	int min , max , i;
	for(i = 0 ; i < n ; i++)
	{
		if(min > q[i])
			min = q[i];
		if(max < r[i])
			max = r[i];
	}
	if(min < 0)
	{
		for(i = 0; i < n ; i++)
		{
			q[i] -= min;
			r[i] -= min;
		}
		MAX = max - min;
	}
}
void swap(int i , int j)
{
	long a = p[i] , b = q[i] , c = r[i];
	p[i] = p[j]; q[i] = q[j]; r[i] = r[j];
	p[j] = a; q[j] = b; r[j] = c;
}

int partition(int left ,int right)
{
	int i = left-1;
	int j;
	for(j = left;j<right;j++)
	{
		if(p[j] <= p[right])
		{
			i++;
			swap(i,j);
		}
	}
	swap(i+1,right);
	return i+1;
}
void quicksort(int left,int right)
{
	if(left < right)
	{
		int q = partition(left,right);
		quicksort(left,q-1);
		quicksort(q+1,right);
	}
}

int main()
{
	generator.init();
	int t = generator.getT();
	while(t--)
	{
		generator.getData(&n,&p,&q,&r);
		int ans = 0;
//		for(int i = 0 ; i < n ; i++)
//			printf("%d %d %d %d\n",n,p[i],q[i],r[i]);
		quicksort(0,n-1);
		printf("\n");
		for(int i = 0;i<n;i++)
		{
			if(q[i] > r[i])
			{
				long temp = q[i];
				q[i] = r[i];
				r[i] = temp;
			}
		}
		for(int i = 0 ; i < n ; i++)
			printf("%d %d %d %d\n",n,p[i],q[i],r[i]);
		move();
		printf("\n");
		for(int i = 0 ; i < n ; i++)
			printf("%d %d %d %d\n",n,p[i],q[i],r[i]);
	}
}
