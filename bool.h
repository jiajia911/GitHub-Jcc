#define _CRT_SECURE_NO_WARNINGS
#ifndef BOOL_H
#define BOOL_H
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<stack>
#include<set>
#include<map>
#include<regex>
#include<queue>

using namespace std;


class analy
{
private:
	class tra
	{
	public:
		string tok;
		int tag;
	};
	stack<string> rem;
	vector<tra> token;
	vector<tra> urt;
	inline bool che(char ch)
	{
		if (ch >= '0' && ch <= '9')
			return true;
		return false;
	}
	inline int gett(string &aim)
	{
		if (aim == "(") return -20;
		if (aim == "<<" || aim == ">>") return -10;
		if (aim == "&" || aim == "|") return -10;
		if (aim == ":") return -4;
		if (aim == "?") return -3;
		if (aim == "==" || aim == ">=" || aim == "<=" || aim == "<" || aim == ">") return 0;
		if (aim == "&&" || aim == "||") return -2;
		if (aim == "!" || aim == "~") return -1;
		if (aim == "+" || aim == "-") return 10;
		if (aim == "*" || aim == "/") return 20;
		if (aim == ")") return 30;
		return 50;
	}
	inline void cle_rem()
	{
		while (!rem.empty())
		{
			tra tem;
			tem.tag = 0; tem.tok = rem.top();
			urt.push_back(tem);
			rem.pop();
		}
	}
	inline void pus(string &aim)
	{
		if (aim == ")")
		{
			while (true)
			{
				string ts = rem.top();
				rem.pop();
				if (ts == "(")
					break;
				else
				{
					tra tem;
					tem.tag = 0; tem.tok = ts;
					urt.push_back(tem);
				}
			}
		}
		else
		{
			if (aim == "(")
				rem.push(aim);
			else
			{
				while (!rem.empty() && gett(rem.top()) >= gett(aim))
				{
					string ts = rem.top();
					tra tem;
					tem.tag = 0; tem.tok = ts;
					urt.push_back(tem);
					rem.pop();
				}
				rem.push(aim);
			}
		}
	}
	inline bool revok(char a, char b)
	{
		if ((a == '&' && b == '&') || (a == '|' && b == '|')
			|| (a == '<' && b == '<') || (a == '>' && b == '>')
			|| (a == '<' && b == '=') || (a == '>' && b == '=') || (a == '=' && b == '='))
			return true;
		return false;
	}
	inline int getnum(tra now)
	{
		int ans = 0;
		sscanf(now.tok.c_str(), "%d", &ans);
		return ans;
	}
	inline int tonum(string &aim)
	{
		int ans = 0;
		sscanf(aim.c_str(), "%d", &ans);
		return ans;
	}
	inline string tostr(int num)
	{
		string le;
		char tst[55];
		sprintf(tst, "%d", num);
		string tem(tst);
		le += tem;
		return le;
	}
	inline string anat()
	{
		stack<tra> sta;
		for (int i = 0; i < urt.size(); ++i)
		{
			if (urt[i].tag)
				sta.push(urt[i]);
			else
			{
				string &opt = urt[i].tok;
				int ans = 0;
				if (opt == "^" || opt == "!")
				{
					int a = getnum(sta.top());
					sta.pop();
					if (opt == "!")
						ans = !a;
					if (opt == "~")
						ans = ~a;
				}
				else
				{
					int b = getnum(sta.top());
					sta.pop();
					int a = getnum(sta.top());
					sta.pop();
					//string opt = urt[i].tok;
					if (opt == "+")
						ans = a + b;
					if (opt == "-")
						ans = a - b;
					if (opt == "*")
						ans = a * b;
					if (opt == "&&")
						ans = a && b;
					if (opt == "||")
						ans = a || b;
					if (opt == "|")
						ans = a | b;
					if (opt == "&")
						ans = a & b;
					if (opt == "<<")
						ans = a << b;
					if (opt == ">>")
						ans = a >> b;
					if (opt == ">=")
						ans = a >= b;
					if (opt == "<=")
						ans = a <= b;
					if (opt == "==")
						ans = a == b;
					if (opt == ">")
						ans = a > b;
					if (opt == "<")
						ans = a < b;
					if (opt == "/")
						ans = a / b;
				}
				tra tes;
				tes.tag = 1;
				tes.tok = tostr(ans);
				sta.push(tes);
			}
		}
		return sta.top().tok;
	}
	inline void pre(string &st)
	{
		string sum, opt;
		token.clear();
		int tag = 0;
		for (auto i = st.begin(); i != st.end(); ++i)
		{
			//	if (*i == ' ')continue;
			if (che(*i))
			{
				if (!opt.empty())
				{
					tra tem;
					tem.tok = opt; tem.tag = 0;
					token.push_back(tem);
					opt.clear();
				}
				sum += *i;
				if (i == st.end() - 1 && !sum.empty())
				{
					tra tem;
					tem.tok = sum; tem.tag = 1;
					token.push_back(tem);
					sum.clear();
				}
			}
			else
			{
				if (!sum.empty())
				{
					tra tem;
					tem.tok = sum; tem.tag = 1;
					token.push_back(tem);
					sum.clear();
				}
				if (!opt.empty() && revok(opt[opt.length() - 1], *i))
				{
					opt += *i;
					tra tem;
					tem.tok = opt; tem.tag = 0;
					token.push_back(tem);
					opt.clear();
				}
				else
				{
					if (!opt.empty())
					{
						tra tem;
						tem.tok = opt; tem.tag = 0;
						token.push_back(tem);
						opt.clear();
					}
					if (*i != ' ')
						opt += *i;
					if (i == st.end() - 1 && !opt.empty())
					{
						tra tem;
						tem.tok = opt; tem.tag = 0;
						token.push_back(tem);
						opt.clear();
					}
				}
			}
		}
		/*for (int i = 0; i < token.size(); ++i)
		cout << token[i].tok << endl;*/
	}
public:
	inline int work(string &st)
	{
		pre(st);
		urt.clear();
		for (int i = 0; i < token.size(); ++i)
		{
			if (token[i].tag)
			{
				urt.push_back(token[i]);
			}
			else
				pus(token[i].tok);
		}
		cle_rem();
		/*	for (int i = 0; i < urt.size(); ++i)
		cout << urt[i].tok;*/
		return  tonum(anat());
	}
};
#endif