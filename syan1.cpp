/**ʶ�����֣�if��int��for��while��do��return��break��continue�������ֱ���Ϊ1��
**�����Ķ�ʶ��Ϊ��ʶ���������ֱ���Ϊ2��
**����Ϊ�޷����������������ֱ���Ϊ3��
**�����������+��-��*��/��=�� ��<�� =��<=��!= ;�����ֱ���Ϊ4��
**�ָ���������,��;��{��}��(��)�� �����ֱ���Ϊ5��
**/
#include <bits/stdc++.h>
using namespace std;
typedef vector<char> vc;

char *key[]={"if","int","for","while","do","return","break","continue"}; //�����ֱ�

vc Biaoshifu(0);   //���һ����ʶ�� 
vc Changshu(0);    //���һ������ 
vc Yunsuan(0);    //���һ������� 
vc v(0);         //���Դ����

void openfile()//���ļ���ɨ��Դ����
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

int Iswhat(char ch)//�ж�һ���ַ���������һ��ġ�
{
    if(ch==' ' || ch=='\n' || ch=='\t') return 0;//�ո�������з���
    else if(ch>='0' && ch<='9') return 1;       //������
    else if((ch>='A' && ch<='Z') || (ch>='a' && ch<='z')) return 2;//��ĸ��
    else if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='=' || ch=='>' || ch=='<' || ch=='!') return 3;//�������
    else if(ch==',' || ch==';' || ch=='(' || ch==')' || ch=='{' || ch=='}') return 4;//�ֽ����
   
}

void Getnum()//��ȡ��ǰ�ĵ�һ�����ִ�����һ�����űض���������
{
    Changshu.clear();//�����������
    int i=0;
    if(Iswhat(v[0])==1)
    while(Iswhat(v[i])==1)
    {
        Changshu.push_back(v[i]);
        i++;
    }
}


void Getbiaoshi()//��ȡ��ǰ�ĵ�һ�����ʴ�,��һ�����űض�����ĸ��
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

int Iskey(vc &p)//�ж��ַ����Ƿ��Ǳ�����,���򷵻�1�����򷵻�0.
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
    cout<<" ��"; 
    for(i=0; i<len; i++)
    {
        cout << q[i];
    }
    cout<<" ��"<<")"; 
    
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
             cout <<"("<< 5<<","<<" ��" << v[i] <<" ��"<<")"<< endl;
              v.erase(n);
         }
         else
         {
             cout << "��ɨ������зǷ��ַ���" << endl;
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
