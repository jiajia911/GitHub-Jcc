#define _CRT_SECURE_NO_WARNINGS
#ifndef DEFINE_H
#define DEFINE_H
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<stack>
#include<set>
#include<map>
#include<regex>
#include"bool.h"

using namespace std;

class def
{
private:
	class neu
	{
	public:
		int a, b;
	};
	class trans
	{
	private:
	public:
		string put;
		int arg;
		int tng = 0;
		vector<neu> vi;
	};
	map<string, trans> che;
	vector<string> nam;
	string su = "__VA_ARGS__";
	string sout;
	analy  bol;
	regex defined;
public:
	inline string secanast(string &st)
	{
		sout.clear();
		string tem = st;
		while (anast(tem))
		{
			tem = sout;
			//	cout << sout<<endl;
			sout.clear();
		}
		return sout;
	}
	inline int anbool(string &aim)
	{
		string st = aim;
		for (sregex_iterator it(st.begin(), st.end(), defined), endi; it != endi; ++it)
		{
			string fmt = "$2";
			string na = regex_replace(it->str(), defined, fmt);
			if (ifde(na))
			{
				fmt = "1";
				st = regex_replace(st, defined, fmt);
			}
			else
			{
				fmt = "0";
				st = regex_replace(st, defined, fmt);
			}
		}
		st += '\n';
		string tem = secanast(st);
		tem.erase(tem.size() - 1);
		//cout << bol.work(tem) << endl;
		return (bol.work(tem));
	}
	inline bool chok(char ch)
	{
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
			(ch >= '0' && ch <= '9') || (ch == '_') || (ch == '.'))
			return true;
		return false;
	}
	inline bool check(char ch)
	{
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
			(ch >= '0' && ch <= '9') )
			return true;
		return false;
	}
	inline void anaexp(string &aim)
	{
		nam.clear();
		string st;
		for (auto i = aim.begin(); i != aim.end(); ++i)
		{
			if ((*i) == ' ') continue;
			if (chok(*i))
				st += (*i);
			else
			{
				nam.push_back(st);
				st.clear();
			}
		}
		if (!st.empty())
			nam.push_back(st);
	}
	inline void anaexp1(string &aim)
	{
		//cout << aim << endl << aim <<endl<< aim << endl;
		nam.clear();
		string st;
		int vis = 0;
		for (auto i = aim.begin(); i != aim.end(); ++i)
		{
			if ((*i) == ' ') continue;
			if (*i == '(') ++vis;
			if (*i == ')') --vis;
			if (!(vis == 0 && (*i) == ','))
				st += (*i);
			else
			{
				nam.push_back(st);
				st.clear();
			}
		}
		if (!st.empty())
			nam.push_back(st);
	}
	inline void firanast(string &st)
	{
		sout.clear();
		string tem = st;
		while (anast(tem))
		{
			tem = sout;
		//	cout << sout<<endl;
			sout.clear();
		}
		cout << sout;
	}
	inline bool anast(string &st)
	{
		int truth = 0;
		string te;
		int t = 0;
		string nam;
		string exp;
		stack<int> rem;
		int sum = 0;
		for (auto i = st.begin(); i != st.end(); ++i)
		{
			if (!t)
			{
				if (chok(*i))
				{
					te += (*i);
				}
				else
				{
					if (che.count(te))
					{
						t = 1;
						//--i;
					}
					else
					{
						sout += te + *i;
						te.clear();
					}
				}
				if (t == 1)
				{
					nam = te;
					te.clear();
				}
			}
			if (t == 1)
			{
				if (che[nam].arg > 0 || che[nam].tng)
				{
					if ((*i) == ' ') continue;
					if ((*i) == ')')
					{
						rem.pop(); --sum;
					}
					if (sum)
						te += (*i);
					if ((*i) == '(')
					{
						rem.push(1); ++sum;
					}
				}
				if (rem.empty())
				{
					exp = te;
					te.clear();
					anaput(nam, exp);
					truth = 1;
					if (che[nam].arg==0 && !che[nam].tng) sout += *i;
					nam.clear();
					exp.clear();
					t = 0;
				}
			}
		}
		return truth;
	}
	inline void pustra(string &le, trans &aim)
	{
		aim.put = le; 
		//cout << aim.put << endl;
		if (aim.put[0] == '#')
		{
			if (aim.put[1] == '@')
			{
				aim.put.erase(0,1);
				aim.put[0] = '\'';
				aim.put += '\'';
			}
			else
			{
				aim.put[0] = '\"';
				aim.put += '\"';
			}
		}
		while (true)
		{
			int j = aim.put.find("##");
			if (j != aim.put.npos)
			{
				aim.put.erase(j, 2);
			}
			else
				break;
		}
	//	cout << aim.put << endl;
		aim.arg = nam.size();
		aim.vi.resize(aim.put.size());
		for (int i = 0; i < nam.size(); ++i)
		{
			//cout << nam[i] << (nam[i]).size()<< endl;
			int j = 0;
			while (true)
			{
				if (nam[i] == "...")
				{
					j = aim.put.find(su, j);
					if (j != aim.put.npos)
					{
						//cout << (nam[i]).size() << endl;
						for (int th = 0; th <su.size()-1; ++th)
						{
							neu ths;
							ths.a = -1;
							ths.b = th;
							aim.vi[j + th] = ths;
						}
						//cout << aim.put << endl;
						j += su.size();
					}
					else
						break;
				}
				else
				{
					j = aim.put.find(nam[i], j);
					int len = aim.put.length();
					if (!((j - 1 >= 0 && check(aim.put[j - 1])) ||
						(j + nam[i].length() <len  && check(aim.put[j + nam[i].length()]))) &&
						j != aim.put.npos)
					{
						//cout << (nam[i]).size() << endl;
						for (int th = 0; th < nam[i].size(); ++th)
						{
							neu ths;
							ths.a = i + 1;
							ths.b = th;
							aim.vi[j + th] = ths;
						}
						//cout << aim.put << endl;
						j += nam[i].size();
					}
					else
						break;
				}
			}

		}
	}
	inline void insert(string &na, string &exp, string &le)
	{
		trans tem;
		tem.tng = 1;
		anaexp(exp);
		pustra(le, tem);
		//che.insert(make_pair(na,tem));
		if (!che.count(na))
			che[na] = tem;
		//cout << na << " " << che.count(na)<<endl;
	}
	inline void insert(string &na)
	{
		trans tem;
		string le;
		string exp;
		anaexp(exp);
		pustra(le, tem);
		//che.insert(make_pair(na,tem));
		if (!che.count(na))
			che[na] = tem;
		//cout << na << " " << che.count(na)<<endl;
	}
	inline void insert(string &na, string &le)
	{
		trans tem;
		string exp;
		anaexp(exp);
		pustra(le, tem);
		//che.insert(make_pair(na,tem));
		if (!che.count(na))
			che[na] = tem;
		//cout << na << " " << che.count(na)<<endl;
	}
	inline void anaput(string &st, string &exp)
	{
		string var;
		if (che.count(st))
		{
			anaexp1(exp);
			trans tem = che[st];
			for (int i = 0; i < tem.put.size(); ++i)
			{
				if (tem.vi[i].a || tem.vi[i].a == -1)
				{
					if (tem.vi[i].a == -1)
					{
						if (var.empty())
						{
							int gus = 0;
							for (int sk = tem.arg - 1; sk < nam.size(); ++sk)
							{
								if (gus)
									var += ',';
								var += nam[sk];
								gus = 1;
							}
						}
						sout += var;
						i = i + su.size() - 1;
					}
					else
						if (!tem.vi[i].b)
							sout += nam[tem.vi[i].a - 1];
				}
				else
					sout += tem.put[i];
			}
		}
	}
	inline int ifde(string &name)
	{
		int ans = che.count(name);
		return ans;
	}
	inline int ifnde(string &name)
	{
		return !ifde(name);
	}
	inline void del(string &name)
	{
		//cout << name << endl;
		if (che.count(name))
		{
			che.erase(name);
		}

	}
	inline void put(string &name)
	{
		if (che.count(name))
		{
			cout << che[name].put << endl;
		}
	}
	def()
	{
		defined.assign("(\\s*defined\\s*)\\((.+?)\\)");
	}
};
#endif