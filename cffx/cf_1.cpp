#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#define N 100	//定义要分析的标识符或常数的最大个数
#define M 20	//标识符的长度

char *sourceFile="C:/Users/JP-PC/Desktop/complier/test.txt";			// 定义进行词法分析的源文件
char *key[8]={"if","else","for","while","do","return","break","continue"};		// 关键字
char *border[6]={",",";","{","}","(",")"};			// 界符定义
char *arithmetic[4]={"+","-","*","/"};			// 算术运算符定义
char *relation[6]={"<","<=","=",">",">=","<>"};	// 关系运算符定义
char *consts[N];							// 常数定义
char *label[N];								// 标识符
int constnum=0,labelnum=0;					// constnum-常数个数;labelnum-标识符个数

// 判断一个字符是不是字母
int Isletter(char ch)
{
	if(ch>='a' && ch<='z'||ch>='A' && ch<='Z')		
		return 1;
	return 0;
}

// 判断一个字符是不是数字
int IsDigit(char ch)
{
	if(ch>='0' && ch<='9')		
		return 1;
	return 0;
}

// 判断单词符号类型
int search(char searchchar[],int wordtype)
{
	int i=0;
	switch (wordtype)
	{
		case 1:
		for (i=0;i<=7;i++)
		{
			if(strcmp(key[i],searchchar)==0)			// 返回具体的关键字
				return(i+1);
		}
		case 2:
		{
			for (i=0;i<=5;i++)
				if(strcmp(border[i],searchchar)==0)	// 返回具体的界符
					return(i+1);       
			return(0);
		}
		case 3:
		{
			for(i=0;i<=3;i++)
				if(strcmp(arithmetic[i],searchchar)==0)	// 返回具体的算术运算符
					return(i+1);
			return(0);
		}
		case 4:
		{
			for(i=0;i<=5;i++)
				if(strcmp(relation[i],searchchar)==0)	// 返回具体的关系运算符
					return(i+1);
			return(0);
		}
		case 5:
		{
			for(i=0;i<constnum;i++)
				if(strcmp(consts[i],searchchar)==0)	// 返回具体的整型常数
					return(i+1);
			consts[i]=(char *)malloc(sizeof(searchchar));
			strcpy(consts[i],searchchar);
			constnum++;
			return(i);
		}
		case 6:
		{
			for(i=0;i<labelnum;i++)
				if(label[i]!=NULL)
					if(strcmp(label[i],searchchar)==0)	// 返回标识符
						return(i+1);
			label[i-1]=(char *)malloc(sizeof(searchchar));
			strcpy(label[i-1],searchchar);
			labelnum++;
			return(i);
		}
	}
	return -1;
}

// 常数处理
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
	dtype=search(digittp,5);							// 输出整型常数
	printf("%s (5, %d)\n",digittp, dtype-1);
	
	return(buffer);
}

// 标识符或关键字
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
	if (atype=search(alphatp,1))						// 输出关键字
		printf("%s (1,%d)\n",alphatp,atype-1);
	else
	{
		atype=search(alphatp,6);					// 输出标识符
		printf("%s (6,%d)\n",alphatp,atype-1);
	}
	
	return(buffer);
}

// 其它处理(运算符,界符等)
char otherprocess(char buffer,FILE* fp)
{
	int i=-1;
	char othertp[M];
	int otype,otypetp;
	othertp[0]=buffer;
	othertp[1]='\0';

	if(otype=search(othertp,3))
	{
		printf("%s (3,%d)\n",othertp,otype-1);
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
			printf("%s (4,%d)\n",othertp,otypetp-1);
			goto out;
		}
		else
			othertp[1]='\0';
		printf("%s (4,%d)\n",othertp,otype-1);
		goto out;
	}
	if(buffer==':')
	{
		buffer=fgetc(fp);
		if (buffer=='=')
			printf(":= (2,2)\n");
		buffer=fgetc(fp);
		goto out;
	}
	else
	{
		if(otype=search(othertp,2))
		{
			printf("%s (2,%d)\n",othertp,otype-1);
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
	FILE *fp;									// 文件指针,指向要分析的源程序
	char cbuffer;								// 保存最新读入的字符
	for (i=0; i<=N; i++)
	{
		label[i]=NULL;							// 初始化标识符
		consts[i]=NULL;						// 初始化常数
	}
	if((fp=fopen(sourceFile,"rb"))==NULL)			// 判断源文件是否存在
		printf("文件%s不存在",sourceFile);
	else
	{
		cbuffer = fgetc(fp);						// 读入字符
		while (cbuffer!=EOF)					// 如果文件没有结束,就一直循环
		{
			if (Isletter(cbuffer))					// 若为字母
				cbuffer=alphaprocess(cbuffer,fp);
			else if (IsDigit(cbuffer))				// 若为数字
				cbuffer=digitprocess(cbuffer,fp);
			else
				cbuffer=otherprocess(cbuffer,fp);
		}
		printf("over\n");
		getchar();
	}
	return 0;
}
