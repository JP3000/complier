#include<string.h>
#include<stdio.h>
#include<stdlib.h> 
#include<ctype.h> 
#include<iostream>
using namespace std;
char*Key[9]={"int","if","for","while","do","return","break","continue"}; char ch; //  �洢ʶ����ĵ�����

 int IsAlpha(char c)
 { 
 // �ж��Ƿ�Ϊ��ĸ  
	if(((c<='z')&&(c>='a'))||((c<='Z')&&(c>='A'))) 
		return 1; 
	else return 0;
 } 
 int IsNum(char c)
 { 
 // �ж��Ƿ�Ϊ����  
	if(c>='0'&&c<='9') 
	 return 1; 
	else return 0; 
 } 
 int IsKey(char *Word)
 { 
 // ʶ��ؼ��ֺ���
	int m,i; 
	for(i=0;i<8;i++){ 
	 if((m=strcmp(Word,Key[i]))==0) 
		 return 1; 
 } 
 return 0; 
 } 
 void scanner(FILE *fp)
 { 
 // ɨ�躯��  
	 char Word[20]={'\0'}; 
	 char ch; int i,c; 
	 ch=fgetc(fp); // ��ȡ�ַ���ָ�� fp ���Զ�ָ����һ���ַ�  
	 if(IsAlpha(ch))
	  { // �жϸ��ַ��Ƿ�����ĸ  
	   Word[0]=ch; ch=fgetc(fp); 
	   i=1; 
	   while(IsNum(ch)||IsAlpha(ch))
	   { // �жϸ��ַ��Ƿ�����ĸ������  
		 Word[i]=ch; 
		 i++; 
		 ch=fgetc(fp); 
	   } 
   Word[i]='\0'; //'\0'  �����ַ����� ( �ո� ) 
   fseek(fp,-1,1); 
   // ����һ���ַ�  
   c=IsKey(Word); // �ж��Ƿ��ǹؼ���  
   if(c==0) 
       cout<<"(2,"<<Word<<')'<<endl;
   else 
     
    // ����ؼ���  
     cout<<"(1,"<<Word<<')'<<endl; 
      } 
   else 
   // ��ʼ�жϵ��ַ�������ĸ
   if(IsNum(ch)){ 
     // �ж��Ƿ�������  
     Word[0]=ch; 
     ch=fgetc(fp); 
     i=1; 
     while(IsNum(ch))
	 { 
       Word[i]=ch; 
       i++; 
       ch=fgetc(fp); 
     } 
     Word[i]='\0'; 
     fseek(fp,-1,1); // ����  
       cout<<"(3,"<<Word<<')'<<endl; 
   } else // ��ʼ�жϵ��ַ�������ĸҲ��������  
   
   { 
	   Word[0]=ch; 
	   switch(ch)
	   { 
		   case'[': 
		   case']': 
		   case'(': 
		   case')': 
		   case'{': 
		   case'}': 
		   case',': 
		   case'"': 
		   case';': 
		   cout<<"(5,"<<Word<<')'<<endl;
			  break; 
		   case'+':ch=fgetc(fp); 
		   if(ch=='='||ch=='+')
		   { 
			   Word[1]=ch; 
			   // ����� "+=" ���жϽ��Ϊ "++" 
			   cout<<"(4,"<<Word<<')'<<endl; 
		   } 
		   else
		   { 
			   fseek(fp,-1,1); 
			 // �жϽ��Ϊ "+" 
			   cout<<"(4,"<<Word<<')'<<endl; 
		   } break; 
		   case'-':ch=fgetc(fp); 
		   if(ch=='='||ch=='-')
		   { 
			   Word[1]=ch;  
			   cout<<"(4,"<<Word<<')'<<endl; 
		   } 
		   else 
		   { 
			 fseek(fp,-1,1); 
			// �жϽ��Ϊ "-"
			 cout<<"(4,"<<Word<<')'<<endl; 
		   }  break; 
		   case'*': 
		   case'/': 
		   case'!': 
		   case'=':ch=fgetc(fp); 
		   if(ch=='=')
		   { 
			   Word[1]=ch; 
			   cout<<"(4,"<<Word<<')'<<endl; 
		   } 
		   else 
		   { 
			   fseek(fp,-1,1); 
			   cout<<"(4,"<<Word<<')'<<endl; 
		   }  break; 
		   case'<':ch=fgetc(fp); 
		   if(ch=='='||ch=='<')
		   { 
			   Word[1]=ch; 
			   cout<<"(4,"<<Word<<')'<<endl; 
		   } 
		 else
		 { 
		   fseek(fp,-1,1); 
		   cout<<"4\t"<<Word<<endl; // �жϽ��Ϊ "<" 
		 } break; 
		 case'>':ch=fgetc(fp); 
		 if(ch=='='||ch=='>') 
		 { 
		   Word[1]=ch;cout<<"(4,"<<Word<<')'<<endl; 
		 } 
		 else 
		 { 
		   fseek(fp,-1,1); 
		   cout<<"(4,"<<Word<<')'<<endl; 
		 } break; 
		default: 
		cout<<"�޷�ʶ���ַ�!"<<endl;
		break;
		}
	}


