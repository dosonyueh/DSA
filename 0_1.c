#include<stdio.h>
#include<stdlib.h>
#define len 10

int comparator(int*,int*,int*,int*);
void subtraction(int*, int*,int*,int*);
void division(int*,int*);
void multi_2(int*,int,int*);
void multi_n(int*,int,int*);
void swap(int*,int*,int*,int*);
int a[len];
int b[len];
int a_r[len];
int b_r[len];
int main()
{
	int i = 0,length_a = 0,length_b = 0,ans = 1;
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
	
	//決定初始大小
	if(length_a > length_b)
	{
		length_l = &length_a;
		length_s = &length_b;
		m = &a_r[0];
		n = &b_r[0];
	}
	if(length_a < length_b)
	{
		length_l = &length_b;
		length_s = &length_a;
		m = &b_r[0];
		n = &a_r[0];
	}
	if(length_a == length_b)
	{
		length_l = &length_a;
		length_s = &length_a;
		for(int i = length_a -1;i>0;i--)
		{
			if(a_r[i] > b_r[i])
			{
				m = &a_r[0];
				n = &b_r[0];
				break;
			}
			else if(b_r[i] > a_r[i])
			{
				m = &b_r[0];
				n = &a_r[0];
				break;
			}
			else if(b_r[i] == a_r[i])
			{}
		}
	}

	while(*length_l != 0 && *length_s != 0)
	{
		if(m[0] % 2 == 0 && n[0] % 2 == 0)
		{
			ans = ans * 2;
			division(m,length_l);
			division(n,length_s);
		}
		else if (n[0] % 2 == 0)
		{
			division(n,length_s);
		}
		else if (m[0] % 2 == 0)
			division(m,length_l);
		
		if(comparator(m,n,length_l,length_s))
			swap(m,n,length_l,length_s);
		subtraction(m,n,length_l,length_s);
	}
	multi_n(n,ans,length_s);
	printf("最大公因數為：");
	for(int j = 0 ; j <*length_s ; j++)
	{printf("%d",n[j]);}

	/*printf("before ll = %d ls = %d\n",*length_l,*length_s);
	for (int j = 0 ; j < *length_l ; j++)
	{
		printf("%d",m[j]);
	}
	printf("\n");
	
	swap(m,n,length_l,length_s);
	
	printf("after ll = %d ls = %d\n",*length_l,*length_s);
	for (int j = 0 ; j < *length_l ; j++)
	{
		printf("%d",m[j]);
	}
	printf("\n");
*/
	//subtraction(m,n,length_l,length_s);
	//division(m,length_l);
	//multiplication(m,2,length_l);
}

void swap(int *m,int *n,int *length_l,int *length_s)
{
	int temp = 0;
	int length_temp = *length_l;
	*length_l = *length_s;
	*length_s = length_temp;
	for(int i = 0 ; i< *length_l ; i++)
	{
		temp = m[i];
		m[i] = n[i];
		n[i] = temp;
	}
}
		


int comparator(int *m,int *n,int *length_l,int *length_s)
{
	if(*length_l > *length_s)
	{
		m = &a_r[0];
		n = &b_r[0];
		return 0;
	}

	else if(*length_l < *length_s)
	{

		m = &b_r[0];
		n = &a_r[0];
		return 1;
	}

	for(int i = *length_l -1;i>0;i--)
	{
		if(m[i] > n[i])
		{
			m = &a_r[0];
			n = &b_r[0];
			return 0;
		}
		else if(b_r[i] > a_r[i])
		{
			m = &b_r[0];
			n = &a_r[0];
			return 1;
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

void multi_2(int *m,int k,int* length)
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
				if(m[j]>10)
				{
					m[j] = m[j]-10;
					carry ++;
				}
			}
		}
	}
	int len_temp = *length;
	while(m[len_temp] != 0)
	{len_temp++;}
	*length = len_temp;
}

void multi_n(int *n,int ans,int*length)
{
	int carry = 0;
	for(int i = 0 ; i < (*length)+2;i++)
		{
			n[i] = n[i]*ans;
			n[i] += carry;
			carry = 0;
			while(n[i]>10)
			{
				carry++;
				n[i] -= 10;
			}
		}
	int len_temp = *length;
	while(n[len_temp] != 0)
	{len_temp++;}
	*length = len_temp;
}

