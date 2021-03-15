#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define len 1000

int comparator(int*,int*,int*,int*);
void subtraction(int*, int*,int*,int*);
void division(int*,int*);
void multi_2(int*,int,int*);
void multi_n(int*,int,int*);
void swap(int*,int*,int*,int*);
int equal(int*,int*,int*,int*);
int* gcd(int*,int*);
int a[len];
int b[len];
int a_r[len];
int b_r[len];

int main()
{
	int l,j,i = 0,length_a = 0,length_b = 0,ans = 1;
	int *n,*m,*length_l,*length_s;	
	char s[len] = {0};
	printf("enter num a\n");
	scanf("%[^\n]",s);
	printf("%s\n",s);
	for(l = 0 ; l<len ; l++)
	{
		if(s[l] == ' ')
		{break;}
		printf("%d",s[l]-'0');
	}
	for(i = 0 ; i<l;i++)
		a[i] = s[i] - '0';
	length_a = l;
	for(j = len-1;j>l+1;j--)
	{
		if(s[j]!=0)
			break;
	}
	length_b = j-l;
	for(i = l+1; i<j+1;i++)
		b[i-l-1] = s[i] - '0';
	printf("l = %d,l_a = %d,l_b = %d\n",l,length_a,length_b);
	for(i = 0 ; i < length_a;i++)
		printf("%d",a[i]);
	for(i = 0 ; i < length_b;i++)
		printf("%d",b[i]);
	
	//反轉陣列順序
	for(int j = 0;j<length_a;j++)
	{a_r[j] = a[length_a - j-1];}
	for(int j = 0;j<length_b;j++)
	{b_r[j] = b[length_b - j-1];}
	for(int j = 0;j<len-1;j++)
	{
		if(a_r[i]>10)
			a_r[i] = 0;
		if(b_r[i]>10)
			b_r[i] = 0;
	}	
	printf("m 0th = %d,n 0th = %d\n",a_r[0],b_r[0]);
	int same = 0;
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
	printf("m 0th = %d,n 0th = %d\n",a_r[0],b_r[0]);
	if(length_a == length_b)
	{
		length_l = &length_a;
		length_s = &length_b;
		for(int i = *length_l -1;i>-1;i--)
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
			{
				same++;
				printf("%dth is same,same = %d \n",i,same);
			}
		}
		if(same == length_a)
		{	
			printf("same!!");
			m = &b_r[0];
			n = &a_r[0];
			printf("最大公因數為:");
			for(int i = length_a-1;i>-1;i--)
			{printf("%d",a_r[i]);}
		}
		printf("m 0th = %d,n 0th = %d\n",m[0],n[0]);
	}
	//division(n,length_s);
	//subtraction(m,n,length_l,length_s);
//	int equ = equal(m,n,length_l,length_s);
//	printf("equ = %d\n",equ);
//	while(1 == 2)
	while(equal(m,n,length_l,length_s))
	{
		if(m[0] % 2 == 0 && n[0] % 2 == 0)
		{
			ans = ans * 2;
			printf("m,n ==even\n");
			division(m,length_l);
			division(n,length_s);
			for(int j = 0 ; j<*length_l;j++)
			{printf("%d",m[j]);}
			printf("\n");
			for(int j = 0 ; j<*length_s;j++)
			{printf("%d",n[j]);}
			printf("\n");
			printf("length_s == %d\n",*length_s);
			printf("length_l == %d\n",*length_l);
		}
		else if (n[0] % 2 == 0)
		{
			printf("n==even,length_l == %d\n",*length_l);
			division(n,length_s);
			for(int j = 0 ; j<*length_s;j++)
			{printf("%d",n[j]);}
			printf("\n");
			printf("length_s == %d\n",*length_s);
			printf("length_l == %d\n",*length_l);
		}
		else if (m[0] % 2 == 0)
		{
			printf("m == even\n");
			division(m,length_l);
			for(int j = 0 ; j<*length_l;j++)
			{printf("%d",m[j]);}
			printf("\n");
			printf("length_s == %d\n",*length_s);
			printf("length_l == %d\n",*length_l);
		}
		if(!equal(m,n,length_l,length_s))
			break;
		if(comparator(m,n,length_l,length_s))
		{
			swap(m,n,length_l,length_s);
		}
		subtraction(m,n,length_l,length_s);
		printf("subing\n");
		for(int j = 0 ; j<*length_l;j++)
		{printf("%d",m[j]);}
		printf("\n");
		for(int j = 0 ; j<*length_s;j++)
		{printf("%d",n[j]);}
		printf("\n");
	}
	multi_n(n,ans,length_s);
	printf("最大公因數為：");
	for(int j = *length_s-1;j>-1;j--)
	{printf("%d",n[j]);}
	printf("\n");
	gcd(n,length_s);

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
	return 0;
}
int* gcd(int *n,int *length_s)
{	
	int tem[*length_s];
	for(int j = 0;j<*length_s;j++)
	{
		tem[j] = n[(*length_s)-1-j];
	}	

	n = &tem[0];
	for(int j = 0;j<*length_s;j++)
	{
		printf("%d",n[j]);
	}
	
	return n;
	
}
void swap(int *m,int *n,int *length_l,int *length_s)
{
	int temp = 0;
	int length_temp = *length_l;
	
	printf("before swapping : m = ");
	for(int j = 0 ; j <*length_l ; j++)
	{printf("%d",m[j]);}
	printf(" n = ");
	for(int j = 0 ; j <*length_s ; j++)
	{printf("%d",n[j]);}
	printf("\n");
	*length_l = *length_s;
	*length_s = length_temp;
	for(int i = 0 ; i< *length_l ; i++)
	{
		temp = m[i];
		m[i] = n[i];
		n[i] = temp;
	}

	printf("after swapping : m = ");
	for(int j = 0 ; j <*length_l ; j++)
	{printf("%d",m[j]);}
	printf(" n = ");
	for(int j = 0 ; j <*length_s ; j++)
	{printf("%d",n[j]);}
	printf("\n");
}
		


int comparator(int *m,int *n,int *length_l,int *length_s)
{
	printf("comparing\n");
	if(*length_l > *length_s)
	{
		printf("m is bigger by length\n");
		return 0;
	}

	else if(*length_l < *length_s)
	{

		printf("n is bigger by length\n");
		return 1;
	}

	for(int i = *length_l -1;i>-1;i--)
	{	int equ = 0;
		if(m[i] > n[i])
		{
		printf("m is bigger by %dth\n",i+1);
			return 0;
		}
		else if(n[i] > m[i])
		{
		printf("n is bigger by %dth\n",i+1);
			return 1;
		}
		else if(m[i] == n[i])
		{}
	}
}


void subtraction(int *m,int *n,int *length_l,int *length_s)
{
	printf("before sub length_l == %d\n",*length_l);
	printf("before sub length_s == %d\n",*length_s);
	printf("before sub length_s add == %p\n",length_s);
	//先對位數較少的做減法
	for (int i = 0;i< *length_l;i++)
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
		{
			m[i] = m[i];
		}
		for(int i = *length_l ; i<len ; i++)
		{
			m[i] = 0;
		}
	}

	int len_temp = *length_l;
	while(m[len_temp-1] == 0)
	{
		len_temp--;
	}
	*length_l = len_temp;

}

void division(int *a,int *length)
{
	for(int i = *length-1 ; i > -1 ; i--)
	{	
		if(a[i] % 2 != 0)
			a[i-1] = a[i-1]+10;
		a[i] = a[i]/2;
	}
	int len_temp = *length;
	while(a[len_temp-1] == 0)
	{len_temp--;}
	*length = len_temp;
	printf("after div length == %d\n",*length);

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

void multi_n(int *n,int ans,int *length)
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

int equal(int *m,int *n,int *length_l,int *length_s)
{
	int i,same = 0;
	printf("m 0th = %d,n 0th = %d\n",m[0],n[0]);
	if(*length_l != *length_s)
		return 1;
	if(*length_l == *length_s)
	{
		for(i = 0 ; i < *length_l; i++)
		{
			if(m[i] != n[i])
			{
				printf("%dth is diff_2\n",i);
				return 1;
			}
			else
			{	
				printf("%dth is same_2\n",i);
				same++;
			}
		}
	}
	if(same == *length_l)
		return 0;
}
