/**识别保留字：if、int、for、while、do、return、break、continue；单词种别码为1。
**其他的都识别为标识符；单词种别码为2。
**常数为无符号整形数；单词种别码为3。
**运算符包括：+、-、*、/、=、 、<、 =、<=、!= ;单词种别码为4。
**分隔符包括：,、;、{、}、(、)； 单词种别码为5。
**/
#include <bits/stdc++.h>
using namespace std;
typedef vector<char> vc;

char *key[]={"if","int","for","while","do","return","break","continue"}; //保留字表

vc Biaoshifu(0);   //存放一个标识符 
vc Changshu(0);    //存放一个常数 
vc Yunsuan(0);    //存放一个运算符 
vc v(0);         //存放源程序串

void openfile()//从文件里扫描源程序
{
    ifstream in_stream;
    in_stream.open("code.txt");
    if(in_stream.fail())
    {
        cout << "Input file opening error!" << endl;
        exit(1);
    }

    char next;
    while(! in_stream.eof())
    {
        in_stream.get(next);
        v.push_back(next);
    }
    v.pop_back();

}

int Iswhat(char ch)//判断一个字符是属于哪一类的。
{
    if(ch==' ' || ch=='\n' || ch=='\t') return 0;//空格符、换行符等
    else if(ch>='0' && ch<='9') return 1;       //数字类
    else if((ch>='A' && ch<='Z') || (ch>='a' && ch<='z')) return 2;//字母类
    else if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='=' || ch=='>' || ch=='<' || ch=='!') return 3;//运算符类
    else if(ch==',' || ch==';' || ch=='(' || ch==')' || ch=='{' || ch=='}') return 4;//分界符类
   
}

void Getnum()//获取当前的第一个数字串，第一个符号必定是数字类
{
    Changshu.clear();//首先清空向量
    int i=0;
    if(Iswhat(v[0])==1)
    while(Iswhat(v[i])==1)
    {
        Changshu.push_back(v[i]);
        i++;
    }
}


void Getbiaoshi()//获取当前的第一个单词串,第一个符号必定是字母类
{
    Biaoshifu.clear();
    int i=0;
    if(Iswhat(v[0])==2)
    while(Iswhat(v[i])==2 ||Iswhat(v[i])==1)
    {
        Biaoshifu.push_back(v[i]);
        i++;
    }
}

void Getyunsuan()
{
    Yunsuan.clear();
    int i=0;
    while(Iswhat(v[i])==3)
    {
        Yunsuan.push_back(v[i]);
        i++;
    }
}

int Iskey(vc &p)//判断字符串是否是保留字,是则返回1，否则返回0.
{
    int i,flag=0;
    char str[100];
    int p_len=p.size();

    for(i=0; i<p_len; i++)
    {
        str[i]=p[i];
    }
    str[i]='\0';
    for(i=0; i<8; i++)
    {
        if(strcmp(str,key[i])==0)
        {
            flag=1;
            return 1;
        }
    }
    if(flag==0) return 0;
}



void print(vc &q)
{
    int i,len=q.size();
    cout<<" “"; 
    for(i=0; i<len; i++)
    {
        cout << q[i];
    }
    cout<<" ”"<<")"; 
    
    cout << endl;
}
void anayse()
{
	vector<char>::iterator n=v.begin();

     int i=0;

     while(! v.empty())
     {
         if(Iswhat(v[i])==0)
         {
             v.erase(n);
         }
         else if(Iswhat(v[i])==1)
         {
             Getnum();
             int len=Changshu.size();
             cout<<"("<< 3<<",";
             print(Changshu);
             while(len--)
             {
                 v.erase(n);
             }
         }
         else if(Iswhat(v[i])==2)
         {
             Getbiaoshi();
             int len=Biaoshifu.size();

             if(Iskey(Biaoshifu)==1)
             {
                 cout <<"("<< 1<<",";
                 print(Biaoshifu);
             }
             else
             {
                 cout <<"("<< 2<<",";
                 print(Biaoshifu);
             }
            while(len--)
             {
                 v.erase(n);
             }
         }
         else if(Iswhat(v[i])==3)
         {
            Getyunsuan();
            cout <<"("<< 4<<",";
            print(Yunsuan);
            int len=Yunsuan.size();
            while(len--)
             {
                  v.erase(n);
             }
         }
         else if(Iswhat(v[i])==4)
         {
             cout <<"("<< 5<<","<<" “" << v[i] <<" ”"<<")"<< endl;
              v.erase(n);
         }
         else
         {
             cout << "待扫描程序含有非法字符！" << endl;
             break;
         }
     }
	
	
}

int main()
{
    openfile();
    anayse();
    return 0;
}
