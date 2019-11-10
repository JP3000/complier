#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
/*1:E->TE' 2:E'->+TE' 3:E'->ε? 4:T->FT' 5:T'->*FT' 6:T'->ε? 7:F->(E) 8:F->i*/
int  ll1[5][6]={{1,0,0,1,0,0},
{0,2,0,0,3,3},
{4,0,0,4,0,0},
{0,6,5,0,6,6},
{8,0,0,7,0,0}}; //表示LL(1)分析表内容
int  main()
{
  char  ch[10]={ '#' , 'E' };  //用于存放符号栈内容
  char  str[10];  //存放输入串
  char  str1[10];  //用于存放最初输入的字符串
  char  cha;  //分析字符
  int  i,j,m,n;  //j：终结符所代表数字;m：非终结符所代表数字;n：产生式右部大小
  int  l=1;  //符号栈大小
  int  k=1;  //分析输入串的第几个字符
  int  how;  //利用 哪 个产生式
  int  step=1;  //步骤
  int  length=0;
 printf( "input a string and end of '#': ");
  do
 {
   scanf( "%c" ,&cha);
   str[length]=cha;
   str1[length]=cha;
   length++;
 } while (cha!= '#' );
 printf( "步骤\t符号栈\t\t输入串\t\t所用产生式\n" );
  do
 {
   cha=str1[k-1];
   printf( "%d\t" ,step);
    for (i=0;i<=l;i++)
     printf( "%c" ,ch[i]);  //输出符号栈
   printf( "\t\t" );
    for (i=k-1;i<length;i++)
     printf( "%c" ,str[i]);
   printf( "\t\t" );
   if((cha >='A' &&  cha <='Z') || (cha >= 'a' && cha <= 'z'))
	{
		j = 0;
	}
    switch (cha)
   {
      case   'i' :
     j=0; break ;
      case   '+' :
     j=1; break ;
      case   '*' :
     j=2; break ;
      case   '(' :
     j=3; break ;
      case   ')' :
     j=4; break ;
      case   '#' :
     j=5; break ;
     defult:
     j=-1; break ;
   }
    if (j!=-1)  //正确的字符
   {
      if (ch[l]!=cha)
     {
        if (ch[l]!=39)
       {
          switch (ch[l])
         {
            case   'E' :
           m=0; break ;
            case   'T' :
           m=2; break ;
            case   'F' :
           m=4; break ;
            default :
           m=-1; break ;
         }
       }
        else
       {
          switch (ch[l-1])
         {
            case   'E' :
           m=1; break ;
            case   'T' :
           m=3; break ;
            default :
           m=-1; break ;
         }
       }
     }
      if (m!=-1)
     {
        if (ch[l]!=cha)
       {
         how=ll1[m][j];
          if (how==1)
         {
           printf( "E->TE'\n" );
           n=3;
           l=l+n-1;
           ch[l]= 'T' ;
           ch[l-1]=39;
           ch[l-2]= 'E' ;
           step=step+1;
         }
          else   if (how==2)
         {
           printf( "E'->+TE'\n" );
           n=4;
           l=l+n-2;
           ch[l]= '+' ;
           ch[l-1]= 'T' ;
           ch[l-2]=39;
           ch[l-3]= 'E' ;
           step=step+1;
         }
          else   if (how==3)
         {
           printf( "E'->ε?\n" );
           l=l-2;
           step=step+1;
         }
          else   if (how==4)
         {
           printf( "T->FT'\n" );
           n=3;
           l=l+n-1;
           ch[l]= 'F' ;
           ch[l-1]=39;
           ch[l-2]= 'T' ;
           step=step+1;
         }
          else   if (how==5)
         {
           printf( "T'->*FT'\n" );
           n=4;
           l=l+n-2;
           ch[l]= '*' ;
           ch[l-1]= 'F' ;
           ch[l-2]=39;
           ch[l-3]= 'T' ;
           step=step+1;
         }
          else   if (how==6)
         {
           printf( "T'->ε?\n" );
           l=l-2;
           step=step+1;
         }
          else   if (how==7)
         {
           printf( "F->(E)\n" );
           n=3;
           l=l+n-1;
           ch[l]= '(' ;
           ch[l-1]= 'E' ;
           ch[l-2]= ')' ;
           step=step+1;
         }
          else   if (how==8)
         {
           printf( "F->%c\n", cha);
           n=1;
           l=l+n-1;
           ch[l]= cha ;
           step=step+1;
         }
          else
         {
           printf( "错误!\n" );
            break ;
         }
       }
        else
       {
          if (cha== '#'  && ch[l]== '#' )
         {
           printf( "成功!\n" );
            break ;
         }
          else
         {
           printf( "\n" );
           l=l-1;
           k=k+1;
           step=step+1;
         }
       }
     }
      else
     {
       printf( "错误!" );
        break ;
     }
   }
    else   //错误的字符
   {
     printf( "错误的字符!" );
      break ;
   }
 } while (l>=0);
 getch();
  return  0;
}	
	


