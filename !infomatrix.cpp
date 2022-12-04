#include <bits/stdc++.h>
#include <math.h>
typedef long long ll;
using namespace std;
ll i, j, a, n, m, b, c, d, f, g, e;
string s[10000], t, st;
vector <pair<string, int>> setir;
vector <pair<pair<int, int>, pair<int, int>>> vcp;
bitset <1000000> bs; 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	ifstream input("base.txt");
	ofstream output("result.txt");
	n=0;
	while (!input.eof())
	{
		input>>s[n];
		n++;
	}
	n--;
	s[n+1]="something1"; s[n+2]="something2";
	bool comment=false;
	bool text=false;
	bool if_=false;
	for (a=0; a<=n; a++)
	{
		4// comment begin
		if (s[a]=="/*") comment=true;
		if (s[a]=="*/") comment=false;
		if (comment) continue;
		// comment_barmy end
		
		t=s[a]; t=t+"      ";
		for (b=0; b<t.length(); b++)
		{
			if (t[b]=='c' and t[b+1]=='o' and t[b+2]=='u' and t[b+3]=='t')
			{
				int pos=b+1;
				for (c=a; c<=n; c++)
				{
					st=s[c];
					st=st+"     ";
					bool dasyna=false;
					for (d=pos; d<st.length(); d++)
					{
						if (st[d]==';')
						{
							dasyna=true;
							break;
						}
						if (st[d]=='e' and st[d+1]=='n' and st[d+2]=='d' and st[d+3]=='l')
						{
							s[c][d]=char(39);
							s[c][d+1]=char(92);
							s[c][d+2]=char(110);
							s[c][d+3]=char(39);
						}
					}
					if (dasyna) break;
					pos=0;
				}
			}
		}
		
		// if begin
		t=s[a]; st=s[a+1];
		if_=false;
		int haysy=0, pos=0;
		if ((t=="if" and st[0]=='(') or t=="if(")
		{
			if (t=="if(")
			{
				haysy=a;
				pos=2;
			}
			else
			{
				haysy=a+1;
				pos=0;
			}
			if_=true;
		}
		
		if (if_==false)
		{
			t=t+" ";
			for (b=0; b<t.length(); b++)
			{
				if (t[b]=='i' and t[b+1]=='f')
				{
					for (c=b+2; c<t.length(); c++)
					{
						if (t[c]==' ') continue;
						if (t[c]=='(')
						{
							haysy=a;
							pos=c;
							if_=true;
						}
						break;
					}
					if (if_==true) break;
				}
			}
		}
		if (if_==true)
		{
			int skobka=0;
			bool and_or=false;
			bool basga=false;
			string if_var="";
			for (b=haysy; b<=n; b++)
			{
				t=s[b];
				t=t+"    ";
				for (c=pos; c<t.length(); c++)
				{
					if (t[c]=='(') skobka++;
					if (t[c]==')') skobka--;
					if (skobka==0)
					{
						if (!basga)
						{
							bool baslady=false, cykdy=false;
							for (d=haysy; d<=n; d++)
							{
								t=s[d];
								t=t+" ";
								for (e=pos+1; e<t.length(); e++)
								{
									if (t[e]!=' ') baslady=true;
									if (t[e]==')' or t[e]=='=' or t[e]==' ') {cykdy=true; break;}
									if (baslady) if_var=if_var+t[e];
								}
								if (cykdy) break;
								pos=0;
							}
						}
						haysy=b;
						pos=c+1;
						break;
					}
					if ((t[c]=='a' and t[c+1]=='n' and t[c+2]=='d') or (t[c]=='o' and t[c+1]=='r') or (t[c]=='&' and t[c+1]=='&') or (t[c]=='|' and t[c+1]=='|'))
					{
						and_or=true;
					}
					if (t[c]=='-' or t[c]=='+' or t[c]=='%' or t[c]=='*' or t[c]=='/') basga=true;
				}
				if (skobka==0) break;
				pos=0;
			}
			if (!and_or)
			{
				bool sony=false;
				bool basga=false;
				int gornus=0;
				int pos_g=pos;
				string var;
				for (b=haysy; b<=n; b++)
				{
					t=s[b];
					t=t+"        ";
					for (c=pos; c<t.length(); c++)
					{
						if (t[c]==';')
						{
							pos=pos_g;
							sony=true;
							break;
						}
						if (t[c]=='+' or t[c]=='=')
						{
							if (t[c]=='+') gornus=1; else gornus=2;
							basga=true;
						}
						if (!basga) var=var+t[c];
					}
					if (sony) break;
					pos=0;
				}
				if (sony)
				{
					string real_var="";
					bool pp=false;
					vcp.push_back(make_pair(make_pair(haysy, pos), make_pair(b, c)));
					for (b=0; b<var.length(); b++)
					{
						if (var[b]!=' ') pp=true;
						if (!pp) continue;
						real_var=real_var+var[b];
					}
					setir.push_back(make_pair(real_var, gornus));
					for (b=0; b<setir.size(); b++)
					{
						if (setir[b].first==if_var and setir[b].second==1)
						{
							auto k1=vcp[b].first;
							auto k2=vcp[b].second;
							s[k1.first]=s[k1.first]+"{";
							s[k2.first]=s[k2.first]+" break; }";
							break;
						}
					}
				}
			}
		}
		//if_gozleg end
	}
	int yay=0;
	for (a=0; a<=n; a++)
	{
		output<<s[a]<<" ";
		char ch=s[a][s[a].length()-1];
		if (ch==';')
		{
			output<<endl;
			for (b=1; b<=yay; b++) output<<" ";	
		}
		if (ch=='{')
		{
			yay=yay+4;
			output<<endl;
			for (b=1; b<=yay; b++) output<<" ";
		}
		if (ch=='}')
		{
			yay=yay-4;
			output<<endl;
			for (b=1; b<=yay; b++) output<<" ";
		}
		t=s[a];
		t="    "+t;
		if (s[a][s[a].length()-1]=='>' and s[a][s[a].length()-2]=='h' and s[a][s[a].length()-3]=='.') output<<endl;
	}

}
/*

*/

