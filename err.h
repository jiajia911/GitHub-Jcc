#define _CRT_SECURE_NO_WARNINGS
#ifndef ERR_H
#define ERR_H
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>

using namespace std;

class err
{
private:
	int cou = 0;
public:
	inline int isError()
	{
		return cou;
	}
	inline void Error(string &er, int aim)
	{
		Error(er);
		exit(aim);
	}
	inline void Error(int aim)
	{
		++cou;
		fprintf(stderr, "Unrecovery run time error detected!\n");
		exit(aim);
	}
	inline void Error()
	{
		++cou;
	}
	inline void Error(string &er)
	{
		fprintf(stderr, er.c_str());
		++cou;
	}
};

#endif