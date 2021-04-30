#include <stdio.h>
#include <stdlib.h>
#include "generator.h"


int main()
{
	generator.init();
	int t = generator.getT();
	printf("%d\n",t);
	while(t--)
	{
		int n,*p,*q,*r;
		generator.getData(&n,&p,&q,&r);
		int ans = 0;
		for(int i = 0 ; i < n ; i++)
			printf("%d %d %d %d\n",n,p[i],q[i],r[i]);
	}
}
