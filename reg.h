#define _CRT_SECURE_NO_WARNINGS
#ifndef REG_H
#define REG_H
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<stack>
#include<set>
#include<map>
#include<regex>
#include"Input.h"
#include"define.h"

using namespace std;



class reg
{
private:
	static const int maxrex = 20;
	string tem = "(#\\s*?include)(\\s*?)(\"|<)(\\s*?)(.+?)(\\s*?)(\"|>)";
	string te = "(#\\s*?include\\s*)(\"|<)(\\s*)(.+?)(\\s*)(\"|>)";
	string te1 = "(#\\s*define\\s+)(\\w+)(\\s*)$";
	string te2 = "(#\\s*define\\s+)(\\w+)(\\s+)(.+)(\\s*)$";
	string te3 = "(#\\s*define\\s+)(\\w+?)\\((.+?)\\)(\\s+)(.+?)(\\s*)$";
	string fe = "(#\\s*define\\s+)(\\w+?)\\((.+?)\\)(\\s+)(.+?)(\\s*)$";
	string fe1 = "(#\\s*error\\s+)(.+?)(\\s*)$";
	string fe2 = "__LINE__";
	string fe3 = "__FILE__";
	string he = "(#\\s*undef\\s+)(\\w+?)(\\s*)$";
	string he1 = "(#\\s*ifdef\\s+)(\\w+?)(\\s*)$";
	string he2 = "(#\\s*ifndef\\s+)(\\w+?)(\\s*)$";
	string he3 = "(#\\s*undef\\s+)(\\w+?)(\\s*)$";
	string ene = "(#\\s*endif)(\\s*)$";
	string se = "(#\\s*if\\s+)(.+)(\\s*)$";
	string se1 = "(#\\s*elif\\s+)(.+?)(\\s*)$";
	string se2 = "(#\\s*else)(\\s*)$";
	regex pat[maxrex];
	Input now;
	int inputsetted = 0;
	int flag = 0;
	def lex;
	//stack<int> state;
	int fla = 0;
public:
	inline void work()
	{

		if (!inputsetted) return;
		string st;
		string temc;
		stack<int> fsh;
		int stage = 0; char last = '\0';
		//cout <<lex.che.count("ECHO") << endl;
		while (!now.ifend())
		{
			while (!now.ifend())
			{
				temc = now.getch();
				if (!temc.empty())
					st += temc;
				if (st.length() > 1 && st[st.length() - 1] == '\n' && st[st.length() - 2] == '\\')
				{
					st.erase(st.length() - 1);
					st.erase(st.length() - 1);
					continue;
				}
				if (!st.empty() && st[st.length() - 1] == '\n') break;
			}
			string fmt;
			int todo = 0,gui = 0;
			for (sregex_iterator it(st.begin(), st.end(), pat[14]), endi; it != endi; ++it)
			{
				if ((fsh.empty()) || (!fsh.empty() && (fsh.top() == 1 || fsh.top() == 3 || fsh.top() == 6)))
				{
					fmt = "$2";
					string na = regex_replace(it->str(), pat[14], fmt);
					if (lex.anbool(na))
					{
						fsh.push(1);
					}
					else
						fsh.push(2);
				}
				else
				{
					fsh.push(15);
				}
				
				st.clear();
				//dtag = 1;
			}
			if (!fsh.empty() && fsh.top() < 15)
			{
				int tetag = 1;
				for (sregex_iterator it(st.begin(), st.end(), pat[15]), endi; it != endi; ++it)
				{
					tetag = 0;
					fmt = "$2";
					if (!fsh.empty() && fsh.top() == 1)
					{
						fsh.pop();
						fsh.push(8);
					}
					else
					{
						string na = regex_replace(it->str(), pat[15], fmt);
						if (lex.anbool(na))
						{
							fsh.pop();
							fsh.push(3);
						}
						else
						{
							fsh.pop();
							fsh.push(4);
						}
					}
					st.clear();
					//dtag = 1;
				}
			}
			if (!fsh.empty() && fsh.top() < 15)
			{
				for (sregex_iterator it(st.begin(), st.end(), pat[16]), endi; it != endi; ++it)
				{
					
					if (!fsh.empty() && (fsh.top() == 2 || fsh.top() == 4))
					{
						fsh.pop();
						fsh.push(6);
					}
					else
					{
						fsh.pop();
						fsh.push(7);
					}
					st.clear();
					//dtag = 1;
				}
			}
			for (sregex_iterator it(st.begin(), st.end(), pat[13]), endi; it != endi; ++it)
			{
				//flag = 0;
				if (!fsh.empty())
				{
					if (fsh.top() == 11)
						fla -= 1;
					fsh.pop();
				}
				else
				{
					fprintf(stderr, "Syntax error in #endif\n");
					//fprintf(stderr, "Unrecovery run time error detected!\n");
					//exit(1);
				}
				st.clear();
				//dtag = 1;
			}
			if (fsh.empty() || fsh.top() == 1 || fsh.top() == 3 || fsh.top() == 6)
			{
				gui = 1;
			}
			else
			{
				gui = 16;
				st = "\n";
			}
			if (gui <=1)
			if (!fla && !st.empty())
			{
				for (sregex_iterator it(st.begin(), st.end(), pat[10]), endi; it != endi; ++it)
				{
					fmt = "$2";
					string na = regex_replace(it->str(), pat[10], fmt);
					if (!lex.ifde(na))
					{
						fsh.push(11);
						fla += 1;
					}
					else
						fsh.push(1);
					st.clear();
					//dtag = 1;
				}
				for (sregex_iterator it(st.begin(), st.end(), pat[11]), endi; it != endi; ++it)
				{
					fmt = "$2";
					string na = regex_replace(it->str(), pat[11], fmt);
					if (!lex.ifnde(na))
					{
						//flag = 1;
						//cout << na << endl;
						fsh.push(11);
						fla += 1;
					}
					else
						fsh.push(1);
					st.clear();
					//dtag = 1;
				}
				//;	if (!st.empty())
				for (sregex_iterator it(st.begin(), st.end(), pat[12]), endi; it != endi; ++it)
				{
					fmt = "$2";
					string na = regex_replace(it->str(), pat[12], fmt);
					lex.del(na);
					st.clear();
					//dtag = 1;
				}

				if (!fla)
				{
					for (sregex_iterator it(st.begin(), st.end(), pat[2]), endi; it != endi; ++it)
					{
						fmt = "$4";
						now.include(regex_replace(it->str(), pat[2], fmt));
						todo = 1;
					}
					if (todo)
					{
						fmt = "";
						st = regex_replace(st, pat[2], fmt);
					}
					for (sregex_iterator it(st.begin(), st.end(), pat[7]), endi; it != endi; ++it)
					{
						fmt = "$2";
						string na = regex_replace(it->str(), pat[7], fmt);
						fprintf(stderr, "#error detected!\n");
						fprintf(stderr, na.c_str());
						exit(0);
						st.clear();
						//dtag = 1;
					}
					fmt = now.getle();
					st = regex_replace(st, pat[8], fmt);
					fmt = now.getnam();
					st = regex_replace(st, pat[9], fmt);
					int dtag = 0;
					for (sregex_iterator it(st.begin(), st.end(), pat[3]), endi; it != endi; ++it)
					{
						fmt = "$2";
						string na = regex_replace(it->str(), pat[3], fmt);
						//string exp;
						//string le;
						lex.insert(na);
						st.clear();
						dtag = 1;
					}
					//if (!dtag)
					for (sregex_iterator it(st.begin(), st.end(), pat[4]), endi; it != endi; ++it)
					{
						fmt = "$2";
						string na = regex_replace(it->str(), pat[4], fmt);
						fmt = "$4";
						//string exp;
						string le = regex_replace(it->str(), pat[4], fmt);
						lex.insert(na, le);
						st.clear();
						dtag = 1;
					}
					//if (!dtag)
					for (sregex_iterator it(st.begin(), st.end(), pat[5]), endi; it != endi; ++it)
					{
						fmt = "$2";
						string na = regex_replace(it->str(), pat[5], fmt);
						fmt = "$3";
						string exp = regex_replace(it->str(), pat[5], fmt);
						fmt = "$5";
						string le = regex_replace(it->str(), pat[5], fmt);
						lex.insert(na, exp, le);
						st.clear();
						dtag = 1;
					}
				}
			}
			if (!fla)
			{
				//cout << endl << endl;
				lex.firanast(st);
			}
			st.clear();
		}
/*		string t = "M_PI";
		lex.put(t);
		t = "ECHO";
		lex.put(t);
		t = "MAX";
		lex.put(t);*/
	}
	inline void set_input(Input &aim)
	{
		now = aim;
		inputsetted = 1;
	}
	reg()
	{
		pat[1].assign(tem);
		pat[2].assign(te);
		pat[3].assign(te1);
		pat[4].assign(te2);
		pat[5].assign(te3);
		pat[6].assign(fe);
		pat[7].assign(fe1);
		pat[8].assign(fe2);
		pat[9].assign(fe3);
		pat[10].assign(he1);
		pat[11].assign(he2);
		pat[12].assign(he3);
		pat[13].assign(ene);
		pat[14].assign(se);
		pat[15].assign(se1);
		pat[16].assign(se2);
		//	stage = 0;
	}
};
#endif