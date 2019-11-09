#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#define N 100	//����Ҫ�����ı�ʶ��������������
#define M 20	//��ʶ���ĳ���

char *sourceFile="C:/Users/JP-PC/Desktop/complier/test.txt";			// ������дʷ�������Դ�ļ�
char *key[8]={"if","else","for","while","do","return","break","continue"};		// �ؼ���
char *border[6]={",",";","{","}","(",")"};			// �������
char *arithmetic[4]={"+","-","*","/"};			// �������������
char *relation[6]={"<","<=","=",">",">=","<>"};	// ��ϵ���������
char *consts[N];							// ��������
char *label[N];								// ��ʶ��
int constnum=0,labelnum=0;					// constnum-��������;labelnum-��ʶ������

// �ж�һ���ַ��ǲ�����ĸ
int Isletter(char ch)
{
	if(ch>='a' && ch<='z'||ch>='A' && ch<='Z')		
		return 1;
	return 0;
}

// �ж�һ���ַ��ǲ�������
int IsDigit(char ch)
{
	if(ch>='0' && ch<='9')		
		return 1;
	return 0;
}

// �жϵ��ʷ�������
int search(char searchchar[],int wordtype)
{
	int i=0;
	switch (wordtype)
	{
		case 1:
		for (i=0;i<=7;i++)
		{
			if(strcmp(key[i],searchchar)==0)			// ���ؾ���Ĺؼ���
				return(i+1);
		}
		case 2:
		{
			for (i=0;i<=5;i++)
				if(strcmp(border[i],searchchar)==0)	// ���ؾ���Ľ��
					return(i+1);       
			return(0);
		}
		case 3:
		{
			for(i=0;i<=3;i++)
				if(strcmp(arithmetic[i],searchchar)==0)	// ���ؾ�������������
					return(i+1);
			return(0);
		}
		case 4:
		{
			for(i=0;i<=5;i++)
				if(strcmp(relation[i],searchchar)==0)	// ���ؾ���Ĺ�ϵ�����
					return(i+1);
			return(0);
		}
		case 5:
		{
			for(i=0;i<constnum;i++)
				if(strcmp(consts[i],searchchar)==0)	// ���ؾ�������ͳ���
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
					if(strcmp(label[i],searchchar)==0)	// ���ر�ʶ��
						return(i+1);
			label[i-1]=(char *)malloc(sizeof(searchchar));
			strcpy(label[i-1],searchchar);
			labelnum++;
			return(i);
		}
	}
	return -1;
}

// ��������
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
	dtype=search(digittp,5);							// ������ͳ���
	printf("%s (5, %d)\n",digittp, dtype-1);
	
	return(buffer);
}

// ��ʶ����ؼ���
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
	if (atype=search(alphatp,1))						// ����ؼ���
		printf("%s (1,%d)\n",alphatp,atype-1);
	else
	{
		atype=search(alphatp,6);					// �����ʶ��
		printf("%s (6,%d)\n",alphatp,atype-1);
	}
	
	return(buffer);
}

// ��������(�����,�����)
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
	FILE *fp;									// �ļ�ָ��,ָ��Ҫ������Դ����
	char cbuffer;								// �������¶�����ַ�
	for (i=0; i<=N; i++)
	{
		label[i]=NULL;							// ��ʼ����ʶ��
		consts[i]=NULL;						// ��ʼ������
	}
	if((fp=fopen(sourceFile,"rb"))==NULL)			// �ж�Դ�ļ��Ƿ����
		printf("�ļ�%s������",sourceFile);
	else
	{
		cbuffer = fgetc(fp);						// �����ַ�
		while (cbuffer!=EOF)					// ����ļ�û�н���,��һֱѭ��
		{
			if (Isletter(cbuffer))					// ��Ϊ��ĸ
				cbuffer=alphaprocess(cbuffer,fp);
			else if (IsDigit(cbuffer))				// ��Ϊ����
				cbuffer=digitprocess(cbuffer,fp);
			else
				cbuffer=otherprocess(cbuffer,fp);
		}
		printf("over\n");
		getchar();
	}
	return 0;
}
