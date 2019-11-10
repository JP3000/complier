#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#define N 100	
#define M 20

<<<<<<< HEAD
char *sourceFile="C:/Users/JP-PC/Desktop/complier/test.txt";			// 定义进行词法分析的源文件
char *key[8]={"if","else","for","while","do","return","break","continue"};		// 关键字
char *border[6]={",",";","{","}","(",")"};			// 界符定义
char *arithmetic[4]={"+","-","*","/"};			// 算术运算符定义
char *relation[6]={"<","<=","=",">",">=","<>"};	// 关系运算符定义
char *consts[N];							// 常数定义
char *label[N];								// 标识符
int constnum=0,labelnum=0;					// constnum-常数个数;labelnum-标识符个数
=======
char *sourceFile="/home/edison/code/c_code/complier/cffx/test.txt";
char *key[8]={"if","else","for","while","do","return","break","continue"}; // 1	
char *label[N];
char *consts[N];
char *oper[10]={"+","-","*","/","<","<=","=",">",">=","<>"};				
char *border[6]={",",";","{","}","(",")"};
>>>>>>> c6b988e4f1db768abc3db8ba11ee6bb666100bee

int constnum=0,labelnum=0;				
int Isletter(char ch)
{
	if(ch>='a' && ch<='z'||ch>='A' && ch<='Z')		
		return 1;
	return 0;
}


int IsDigit(char ch)
{
	if(ch>='0' && ch<='9')		
		return 1;
	return 0;
}


int search(char searchchar[],int wordtype)
{
	int i=0;
	switch (wordtype)
	{
		case 1:
		for (i=0;i<=7;i++)
		{
			if(strcmp(key[i],searchchar)==0)	
				return(i+1);
		}
		case 2:
		{
			for(i=0;i<labelnum;i++)
				if(label[i]!=NULL)
					if(strcmp(label[i],searchchar)==0)
						return(i+1);
			label[i-1]=(char *)malloc(sizeof(searchchar));
			strcpy(label[i-1],searchchar);
			labelnum++;
			return(i);
		}
	    case 3:
		{
        	for(i=0;i<constnum;i++)
				if(strcmp(consts[i],searchchar)==0)	
					return(i+1);
			consts[i]=(char *)malloc(sizeof(searchchar));
			strcpy(consts[i],searchchar);
			constnum++;
			return(i);
		}
		case 4:
		{
			for(i=0;i<=9;i++)
				if(strcmp(oper[i],searchchar)==0)	
					return(i+1);
			return(0);
		}
	
	    case 5:
		{
			for (i=0;i<=5;i++)
				if(strcmp(border[i],searchchar)==0)	
					return(i+1);       
			return(0);
		}
    }
	return -1;
}
char digitprocess(char buffer,FILE* fp)
{
	int i=-1;
	char digittp[M];
	int dtype;
	
	while ((IsDigit(buffer)))
	{
		digittp[++i]=buffer;
		buffer=fgetc(fp);
	}
	digittp[i+1]='\0';
<<<<<<< HEAD
	dtype=search(digittp,5);							// 输出整型常数
	printf("%s (5, %d)\n",digittp, dtype-1);
=======
	dtype=search(digittp,3);							
	printf("(3, ' %s ')\n",digittp);
>>>>>>> c6b988e4f1db768abc3db8ba11ee6bb666100bee
	
	return(buffer);
}
char alphaprocess(char buffer,FILE* fp)
{
	int atype;
	int i=-1;
	char alphatp[M];

	while ((Isletter(buffer))||(IsDigit(buffer)))
	{
		alphatp[++i]=buffer;
		buffer=fgetc(fp);
	}
	alphatp[i+1]='\0';
	if (atype=search(alphatp,1))						
		printf("(1, ' %s ')\n",alphatp);
	else
	{
		atype=search(alphatp,2);				
		printf("(2, ' %s ')\n",alphatp);
	}
	
	return(buffer);
}


char otherprocess(char buffer,FILE* fp)
{
	int i=-1;
	char othertp[M];
	int otype,otypetp;
	othertp[0]=buffer;
	othertp[1]='\0';

	if(otype=search(othertp,4))
	{
		printf("(4, ' %s ')\n",othertp);
		buffer=fgetc(fp);
		goto out;
	}
	if(otype=search(othertp,4))
	{
		buffer=fgetc(fp);
		othertp[1]=buffer;
		othertp[2]='\0';
		if(otypetp=search(othertp,4))
		{
			printf("(4, ' %s ')\n",othertp);
			goto out;
		}
		else
			othertp[1]='\0';
		printf("(4, ' %s ')\n",othertp);
		goto out;
	}
	if(buffer==':')
	{
		buffer=fgetc(fp);
		if (buffer=='=')
			printf(":= (2)\n");
		buffer=fgetc(fp);
		goto out;
	}
	else
	{
		if(otype=search(othertp,5))
		{
			printf("(5, ' %s ')\n",othertp);
			buffer=fgetc(fp);
			goto out;
		}
	}
	if((buffer!='\n')&&(buffer!=' '))
		printf("%c error,not a word\n",buffer);
	buffer=fgetc(fp);
	out: return(buffer);
}

int main(int argc, char* argv[])
{
	int i;
	FILE *fp;							
	char cbuffer;								
	for (i=0; i<=N; i++)
	{
		label[i]=NULL;					
		consts[i]=NULL;					
	}
	if((fp=fopen(sourceFile,"rb"))==NULL)			
		printf("file %s not exist!",sourceFile);
	else
	{
		cbuffer = fgetc(fp);				
		while (cbuffer!=EOF)					
		{
			if (Isletter(cbuffer))					
				cbuffer=alphaprocess(cbuffer,fp);
			else if (IsDigit(cbuffer))				
				cbuffer=digitprocess(cbuffer,fp);
			else
				cbuffer=otherprocess(cbuffer,fp);
		}
		printf("over\n");
		getchar();
	}
	return 0;
}
