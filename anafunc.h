#define _CRT_SECURE_NO_WARNINGS
#ifndef FUNCTION_H
#define FUNCTION_H
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
class func
{
private:
	regex fu, pre;
	Input inp;
	FILE *fot;
	int inputsetted = 0, outputsetted = 0;
public:
	inline void work()
	{
		if (!inputsetted) return;
		string st;
		string temc;
		string funcna;
		int cou = 0;
		while (!inp.ifend())
		{
			while (!inp.ifend())
			{
				temc = inp.regetch();
				if (!temc.empty())
					st += temc;
				if (!st.empty() && st[st.length() - 1] == '\n') break;
			}
			string fmt;
			for (sregex_iterator it(st.begin(), st.end(), pre), endi; it != endi; ++it)
			{
				fmt = "$3";
				funcna = regex_replace(it->str(), pre, fmt);
				//cout << name << endl;
			}
			if (!funcna.empty())
			{
				fmt = funcna;
				st = regex_replace(st, fu, fmt);
			}
			//fprintf(fot,st.c_str());
			cout << st;
			st.clear();
		}
	}
	inline void setInput(Input &aim)
	{
		inp = aim;
		inputsetted = 1;
	}
	inline void setOutput(string &na)
	{
		fot = fopen(na.c_str(),"w");
		outputsetted = 1;
	}
	func()
	{
		fu.assign("__FUNCTION__");
		pre.assign("(\\s*?\\w+)(\\s+)(\\w+)(\\s*)\\((.+)\\)");
	}
};

#endif