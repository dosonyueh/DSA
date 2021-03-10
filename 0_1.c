#include<stdio.h>
#include<stdlib.h>
#define len 10

int comparator(int[],int[],int,int);
void subtraction(int*, int*,int*,int*);
void division(int*,int*);
void multiplication(int*,int,int*);
void abc();
int a[len];
int b[len];
int a_r[len];
int b_r[len];
int ans = 1;
int main()
{
	int i = 0,length_a = 0,length_b = 0;
	int *n,*m,*length_l,*length_s;
	printf("enter num a\n");
	while(1)
	{
		scanf(" %d",&a[i]);
		if(a[i]>=10)
			break;
		i++;
		length_a++;
	}
	/*for(i = 0;i<lenth;i++)
	{
		printf("%d",a[i]);
	}*/
	i = 0;
	printf("enter num b\n");
	while(1)
	{
		scanf(" %d",&b[i]);
		if(b[i]>=10)
			break;
		i++;
		length_b++;
	}
	//反轉陣列順序
	for(int j = 0;j<length_a;j++)
	{a_r[j] = a[length_a - j-1];}
	for(int j = 0;j<length_b;j++)
	{b_r[j] = b[length_b - j-1];}

	(length_a > length_b) ? (length_l = &length_a):(length_l = &length_b);
	(length_a < length_b) ? (length_s = &length_a):(length_s = &length_b);
	if(length_a == length_b)
	{
		length_l = &length_a;
		length_s = &length_a;
	}

	int compare = comparator(a_r,b_r,length_a,length_b);

	if(compare == 1)
	{
		m = &a_r[0];
		n = &b_r[0];
	}
	else if(compare == 2)
	{
		m = &b_r[0];
		n = &a_r[0];
	}
	/*printf("%d\n",compare);
	printf("l_%d\n",*length_l);
	printf("a_%d\n",length_a);
	printf("b_%d\n",length_b);
	for(int j = 0; j<length_s;j++)
	{
		printf("%d",*(n+j));
	}
	for(int j = 0; j<length_l;j++)
	{
		printf("%d",*(m+j));
	}*/
	subtraction(m,n,length_l,length_s);
	//division(m,length_l);
	multiplication(m,2,length_l);
	for(int j = 0; j<*length_l;j++)
	{
		printf("%d\n",m[j]);
	}
	/*while(1)
	{
		int zero_m = 0,zero_n = 0;
		for(int i = 0 ; i<len ;i++)
		{
			if(m[i] == 0)
				zero_m++;
			if(n[i] == 0)
				zero_n++;
		}
		if(zero_m == len && zero_n == len)
			break;

		if(m[0] % 2 == 0 && n[0] % 2 == 0)
		{
			ans = ans * 2;
			division(m,length_l);
			division(n,length_s);
		}
		else if(n[0] % 2 == 0)
		{
			division(n,length_s);
		}
		else if(m[0] % 2 == 0)
		{
			division(m,length_l);
		}
	*/
}

int comparator(int a_r[],int b_r[],int length_a,int length_b)
{
	if(length_a > length_b)
		return 1;
	else if(length_a < length_b)
		return 2;

	for(int i = length_a -1;i>0;i--)
	{
		if(a_r[i] > b_r[i])
		{
			return 1;
		}
		else if(b_r[i] > a_r[i])
		{
			return 2;
		}
		else if(b_r[i] == a_r[i])
		{}
	}

}


void subtraction(int *m,int *n,int *length_l,int *length_s)
{
	//先對位數較少的做減法
	for (int i = 0;i< *length_s;i++)
	{
		if(m[i] >= n[i])
			m[i] = m[i] - n[i];
		else if(m[i] < n[i])
		{
			m[i] = m[i]+10;
			m[i+1] --;
			m[i] = m[i] - n[i];
		}
	}
	//將較高位數放入結果中
	if(*length_l > *length_s)
	{
		for(int i = *length_s ; i < *length_l;i++)
			m[i] = m[i];
		for(int i = *length_l ; i<len ; i++)
			m[i] = 0;
	}

	int len_temp = *length_l;
	while(m[len_temp-1] == 0)
	{len_temp--;}
	*length_l = len_temp;

}

void division(int *m,int *length_l)
{
	for(int i = *length_l-1 ; i > -1 ; i--)
	{
		if(m[i] % 2 != 0)
			m[i-1] = m[i-1]+10;
		m[i] = m[i]/2;
	}
	int len_temp = *length_l;
	while(m[len_temp-1] == 0)
	{len_temp--;}
	*length_l = len_temp;

}

void multiplication(int *m,int k,int* length)
{
	int carry = 0;
	for(int i = 0;i<k;i++)
	{
		for(int j = 0;j<*length;j++)
		{
			m[j] = m[j]*2;
			if(carry == 1)
			{
				m[j]++;
				carry--;
			}

			if(m[j]>10)
			{
				m[j] = m[j]-10;
				carry ++;
			}
		}
	}
	int len_temp = *length;
	while(m[len_temp] != 0)
	{len_temp++;}
	*length = len_temp;
}
