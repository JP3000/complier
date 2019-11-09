#include<iostream>
#include <edge.h>
using namespace std;

edge::edge()
{
	cin>>left>>right;
	rlen=right.length();
	if(NODE.find(left)>NODE.length())
	   NODE+=left;
}

string edge::getlf()
{
	return left;
}

string edge::getrg()
{
	return right;
}

string edge::getfirst()
{
	return first;
}

string edge::getfollow()
{
	return follow;
}

string edge::getselect()
{
	return select;
}

string edge::getro()
{
	string str;
	str+=right[0];
	return str;
}

int edge::getrlen()
{
	return right.length();
}

void edge::newfirst(string w)
{
	int i;
	for(i=0;i<w.length();i++)
		if(first.find(w[i])>first.length())
		first+=w[i];
}

void edge::newfollow(string w)
{
	int i;
	for(i=0;i<w.length();i++)
		if(follow.find(w[i])>follow.length()&&w[i]!='@')
		follow+=w[i];
}

void edge::newselect(string w)
{
	int i;
	for(i=0;i<w.length();i++)
	   if(select.find(w[i])>select.length()&&w[i]!='@')
		select+=w[i];
}

void edge::delfirst()
{
	int i=first.find('@');
	first.erase(i,1);
}
int SUM;
string NODE,ENODE;

//计算first
void first(edge ni,edge *n,int x)
{
	int i,j;
	for(j=0;j<SUM;j++)
	{
		if(ni.getlf()==n[j].getlf())
		{
			if(NODE.find(n[j].getro())<NODE.length())
			{
			 for(i=0;i<SUM;i++)
			  if(n[i].getlf()==n[j].getro())
			   first(n[i],n,x);
			}
			else
			 n[x].newfirst(n[j].getro());
		}
	}
}

//计算follow
void follow(edge ni,edge *n,int x)
{
	int i,j,k,s;
	string str;
	for(i=0;i<ni.getrlen();i++)
	{
		s=NODE.find(ni.getrg()[i]);
		if(s<NODE.length()&&s>-1) //是非终结符
		if(i<ni.getrlen()-1) //不在最右
		for(j=0;j<SUM;j++)
		if(n[j].getlf().find(ni.getrg()[i])==0)
		{
			if(NODE.find(ni.getrg()[i+1])<NODE.length())
			{
				for(k=0;k<SUM;k++)
				 if(n[k].getlf().find(ni.getrg()[i+1])==0)
				 {
				  n[j].newfollow(n[k].getfirst());
				  if(n[k].getfirst().find("@")<n[k].getfirst().length())
				   n[j].newfollow(ni.getfollow());
				 }
			}
			else
			{
				str.erase();
				str+=ni.getrg()[i+1];
				n[j].newfollow(str);
			}
		}	
	}
}

//计算select
void select(edge &ni,edge *n)
{
	int i,j;
	if(ENODE.find(ni.getro())<ENODE.length())
	{
		ni.newselect(ni.getro());
		if(ni.getro()=="@")
		ni.newselect(ni.getfollow());
	}
	else
	for(i=0;i<ni.getrlen();i++)
	{
		for(j=0;j<SUM;j++)
		if(ni.getrg()[i]==n[j].getlf()[0])
		{
			ni.newselect(n[j].getfirst());
			if(n[j].getfirst().find('@')>n[j].getfirst().length())
			return;
		}
	}
}

//输出集合
void out(string p)
{
	int i;
	if(p.length()==0)
	   return;
	cout<<"{";
	for(i=0;i<p.length()-1;i++)
	{
	   cout<<p[i]<<",";
	}
	cout<<p[i]<<"}";
}

//连续输出符号
void outfu(int a,string c)
{
	int i;
	for(i=0;i<a;i++)
	cout<<c;
}


//输出预测分析表
void outgraph(edge *n,string (*yc)[50])
{
	int i,j,k;
	bool flag;
	for(i=0;i<ENODE.length();i++)
	{
	   if(ENODE[i]!='@')
	   {
			outfu(10," ");
			cout<<ENODE[i];
	   }
	}
	outfu(10," ");
	cout<<"#"<<endl;
	int x;
	for(i=0;i<NODE.length();i++)
	{
		outfu(4," ");
		cout<<NODE[i];
		outfu(5," ");
		for(k=0;k<ENODE.length();k++)
		{
			flag=1;
			for(j=0;j<SUM;j++)
			{
				 if(NODE[i]==n[j].getlf()[0])
				 {
					  x=n[j].getselect().find(ENODE[k]);
					  if(x<n[j].getselect().length()&&x>-1)
					  {
						   cout<<"->"<<n[j].getrg();
						   yc[i][k]=n[j].getrg();
						   outfu(9-n[j].getrlen()," ");
						   flag=0;
					  }
					  x=n[j].getselect().find('#');
					  if(k==ENODE.length()-1&&x<n[j].getselect().length()&&x>-1)
					  {
						   cout<<"->"<<n[j].getrg();
						   yc[i][j]=n[j].getrg();
					  }
				 }
			}
			if(flag&&ENODE[k]!='@')
			 outfu(11," ");
		}
		cout<<endl;
	}
}

//分析符号串
int pipei(string &chuan,string &fenxi,string (*yc)[50],int &b)
{
	char ch,a;
	int x,i,j,k;
	b++;
	cout<<endl<<" "<<b;
	if(b>9)
	   outfu(8," ");
	else
	   outfu(9," ");
	cout<<fenxi;
	outfu(26-chuan.length()-fenxi.length()," ");
	cout<<chuan;
	outfu(10," ");
	a=chuan[0];
	ch=fenxi[fenxi.length()-1];
	x=ENODE.find(ch);
	if(x<ENODE.length()&&x>-1)
	{
	   if(ch==a)
	   {
			fenxi.erase(fenxi.length()-1,1);
			chuan.erase(0,1);
			cout<<"'"<<a<<"'匹配";
			if(pipei(chuan,fenxi,yc,b))
			 return 1;
			else
			 return 0;
	   }
	   else
			return 0;
	}
	else
	{
	   if(ch=='#')
	   {
		if(ch==a)
		{
			 cout<<"分析成功"<<endl;
			 return 1;
		}
		else
			return 0;
	   }
	   else
		if(ch=='@')
		{
			 fenxi.erase(fenxi.length()-1,1);
			 if(pipei(chuan,fenxi,yc,b))
			  return 1;
			 else
			  return 0;
		}
		else
		{
		 i=NODE.find(ch);
		 if(a=='#')
		 {
			  x=ENODE.find('@');
			  if(x<ENODE.length()&&x>-1)
			   j=ENODE.length()-1;
			  else
			   j=ENODE.length();
		 }
		 else
			j=ENODE.find(a);
		 if(yc[i][j].length())
		 {
			  cout<<NODE[i]<<"->"<<yc[i][j];
			  fenxi.erase(fenxi.length()-1,1);
			  for(k=yc[i][j].length()-1;k>-1;k--)
			   if(yc[i][j][k]!='@')
				fenxi+=yc[i][j][k];
			  if(pipei(chuan,fenxi,yc,b))
			   return 1;
			  else
			   return 0;
		 }
		 else
			return 0;
		}
	}
}


void main()
{
	edge *n;
	string str,(*yc)[50];
	int i,j,k;
	bool flag=0;
	cout<<"请输入上下文无关文法的总规则数："<<endl;
	cin>>SUM;
	cout<<"请输入具体规则（格式：左部 右部，@为空）："<<endl;
	n=new edge[SUM];
	for(i=0;i<SUM;i++)
	   for(j=0;j<n[i].getrlen();j++)
	   {
			str=n[i].getrg();
			if(NODE.find(str[j])>NODE.length()&&ENODE.find(str[j])>ENODE.length())
			ENODE+=str[j];
	   }
	//计算first集合
	for(i=0;i<SUM;i++)
	{
	   first(n[i],n,i);
	}
	//outfu(10,"~*~");cout<<endl;
	for(i=0;i<SUM;i++)
	   if(n[i].getfirst().find("@")<n[i].getfirst().length())
	   {
			if(NODE.find(n[i].getro())<NODE.length())
			{
				 for(k=1;k<n[i].getrlen();k++)
				 {
					  if(NODE.find(n[i].getrg()[k])<NODE.length())
					  {
						   for(j=0;j<SUM;j++)
						   {
								if(n[i].getrg()[k]==n[j].getlf()[0])
								{
									 n[i].newfirst(n[j].getfirst());
									 break;
								}
						   }
						   if(n[j].getfirst().find("@")>n[j].getfirst().length())
						   {
								n[i].delfirst();
								break;
						   }
					  }
				 }	
			}
	   }
	//计算follow集合
	for(k=0;k<SUM;k++)
	{
	   for(i=0;i<SUM;i++)
	   {
			if(n[i].getlf()==n[0].getlf())
			 n[i].newfollow("#");
			follow(n[i],n,i);
	   }
	   for(i=0;i<SUM;i++)
	   {
			for(j=0;j<SUM;j++)
			 if(n[j].getrg().find(n[i].getlf())==n[j].getrlen()-1)
			  n[i].newfollow(n[j].getfollow());
	   }
	}
	//计算select集合
	for(i=0;i<SUM;i++)
	{
	   select(n[i],n);
	}
	for(i=0;i<NODE.length();i++)
	{
	   str.erase();
	   for(j=0;j<SUM;j++)
		if(n[j].getlf()[0]==NODE[i])
		{
			if(!str.length())
			str=n[j].getselect();
			else
			{
				for(k=0;k<n[j].getselect().length();k++)
				if(str.find(n[j].getselect()[k])<str.length())
				{
					flag=1;
					break;
				}
			}
		}
	}
	//输出
	cout<<endl<<"非终结符";
	outfu(SUM," ");
	cout<<"First";
	outfu(SUM," ");
	cout<<"Follow"<<endl;
	outfu(5+SUM,"-*-");
	cout<<endl;
	for(i=0;i<NODE.length();i++)
	{
	   for(j=0;j<SUM;j++)
		if(NODE[i]==n[j].getlf()[0])
		{
			 outfu(3," ");
			 cout<<NODE[i];
			 outfu(SUM+4," ");
			 out(n[j].getfirst());
			 outfu(SUM+4-2*n[j].getfirst().length()," ");
			 out(n[j].getfollow());
			 cout<<endl;
			 break;
		}
	}
	outfu(5+SUM,"-*-");
	cout<<endl<<"判定结论：    ";
	if(flag)
	{
	   cout<<"该文法不是LL(1)文法!"<<endl;
	   return;
	}
	else
	{
	   cout<<"该文法是LL(1)文法!"<<endl;

	}
	//输出预测分析表
	cout<<endl<<"预测分析表如下："<<endl;
	yc=new string[NODE.length()][50];
	outgraph(n,yc);
	string chuan,fenxi,fchuan;
	cout<<endl<<"请输入符号串：";
	cin>>chuan;
	fchuan=chuan;
	fenxi="#";
	fenxi+=NODE[0];
	i=0;
	cout<<endl<<"预测分析过程如下："<<endl;
	cout<<"步骤";
	outfu(7," ");
	cout<<"分析栈";
	outfu(10," ");
	cout<<"剩余输入串";
	outfu(8," ");
	cout<<"推导所用产生式或匹配";
	if(pipei(chuan,fenxi,yc,i))
	   cout<<endl<<"输入串"<<fchuan<<"是该文法的句子！"<<endl;
	else
	   cout<<endl<<"输入串"<<fchuan<<"不是该文法的句子！"<<endl;
}
