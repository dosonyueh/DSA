#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define L 1000000
#define N 100000
char stack[100000];
double dstack[10000];
int top=-1;
int dtop=-1;

bool isempty(){
	return (top < 0 ? true : false);
}

bool disempty(){
	return (dtop<0?true:false);
}

void push(char a){
	if(top>=L-1){
		printf("full");
		exit(-1);
	}
	stack[++top]=a;
}

void dpush(double a){
	if(dtop>=L-1){
		printf("full");
		exit(-1);
	}
	dstack[++dtop] = a;
}

char pop(){
	if(isempty()){
		printf("empty");
		exit(-1);
	}
	return stack[top--];
}

double dpop(){
	if(disempty()){
		printf("empty");
		exit(-1);
	}
	return dstack[dtop--];
}

char check_top(){
	return stack[top];
}
char dcheck_top(){
	return dstack[top];
}

double interge(){
	int index=0;
	double num1=0;
	double num2=1;
	while(!disempty()){
		num2 = dpop();
		for(int i=0;i<index;i++)num2 = num2*10;
		num1 = num1 + num2;
		index++;
	}
	dpush(num1);
}


int prio(char a){
	char p[5]={'(','+','-','*','/'};
	int Prio[5]={0,1,1,2,2};
	int i;
	for(i=0;i<5;i++){
		if(p[i]==a)return Prio[i];
	}
	return -1;
}

double *change(char *in,double *po){
	int i=0,j=-1,k=1,l=1;
	char x,y;
	while((x=in[i++])!= '#'){
		switch(x){
			case '(':
				push(x);
				if((in[i] == '-'))po[++j]=0;
				if(in[i]>='0' && in[i] <='9'){
					push('+');
					po[++j]=0;
				}
				break;
			case ')':
				if(!disempty()){
					interge();
					po[++j] = dpop();
				}
				while( !isempty() && (x=pop())!='('){
					po[++j] = x-'0';
				}
				break;
			case '+':
			case '-':
			case '*':
			case '/':y=check_top();
				 if(!disempty()){
					 interge();
					 po[++j] = dpop();}
				 while(prio(y) >= prio(x)){
					 po[++j] = pop()-'0';
					 y=check_top();
				 }
				 push(x);
				 break;
			default:dpush(x-'0');
		}
		if(j>=N*l-1)po=realloc(po,sizeof(double)*(++l)*N);
	}
	while(!disempty()){
		interge();
		if(j>=N*l-1)
			po=realloc(po,sizeof(double)*(++l)*N);
		po[++j] = dpop();
	}
	while(!isempty()){
		if(j>=N*l-1)
			po=realloc(po,sizeof(double)*(++l)*N);
		po[++j]=pop()-'0';
	}
	po[++j]='#'-'0';
	return po;
}

double cal(double *po){
	int index=-1;
	while(po[index++]+'0'!='#'){
		while(po[index] >=0){
			dpush(po[index++]);
		}
		double op1;
		double op2;
		double c=0;
		if(disempty()) op1=0;
		else op1=dpop();
		if(disempty()) op2=0;
		else op2=dpop();
		char s=po[index]+'0';
		if(s!='0'){
			switch(s){
				case '+':c=op2+op1;
					 break;
				case '-':c=op2-op1;
					 break;
				case '*':c=op2*op1;
					 break;
				case '/':c=op2/op1;
					 break;
				case '#':c=op1+op2;
			}
		}
		else c = op1+op2;
		dpush(c);
	}
	return dpop();   
}

int main(){
	double *po=malloc(sizeof(double)*N);
	char **al=malloc(sizeof(char *)*L);
	int index=0,i,k=1,j=1;
	double *ans=malloc(sizeof(double)*N);
	while(1){
		char *str=malloc(sizeof(char)*L);
		if(fgets(str,L,stdin)==NULL)break;
		al[index]=str;
		for(i=0;i<L;i++){
			if(al[index][i] == '\n')al[index][i] ='#';
		}
		if(index>=L*k-1){
			al = realloc(al,sizeof(char *)*L*(++k));
		}
		po=change(al[index],po);
		ans[index]=cal(po);
		index++;
		if(index>=N*j-1){
			ans = realloc(ans,sizeof(double)*(++j)*N);
		}
	}
	for(i=0;i<index;i++)printf("%8.15f\n",ans[i]);
	//double ans;
	//    //for(i=0;i<index;i++){
	//            //po=change(al[i],po);
	//                    ////memset(al[i],0,sizeof(al[i]));
	//                            //free(al[i]);
	//                                    //ans=cal(po);
	                                            //printf("%8.15f\n",ans);
	                                                //}
	    free(al);
		return 0;
	}
	                                                        
