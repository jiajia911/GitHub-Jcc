#define _CRT_SECURE_NO_WARNINGS
#ifndef INPUT_H
#define INPUT_H
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<stack>
#include<set>
#include"err.h"

using namespace std;

class Input
{
private:
	//static const int maxbuf = 1024;
	class Inp_rem
	{
	public:
		string name;
		FILE *ft;
		int lin = 0;
	};
	stack<Inp_rem> filnam;
	set<string> vis;
	int flag = 0,fstr =0,cou = 0;
	//int tag = 0;
	char ren[3];
	err ero;
	inline string del_work(char ch)
	{
		//char ch;
		string out;
			if (flag == 0 && ch == '/')
				flag = 1;
			else
				if (flag == 1 && ch == '*')
					flag = 2;
				else
					if (flag == 1 && ch == '/')
						flag = 4;
					else
						if (flag == 1)
						{
							flag = 0;
							out += '/';
						}
						else
							if (flag == 2 && ch == '*')
								flag = 3;
							else
								if (flag == 2)
									flag = 2;
								else if (flag == 3 && ch == '/')
									flag = 0;
								else if (flag == 3 && ch != '*')
									flag = 2;
								else
									if (flag == 4 && ch == '\\')
										flag = 9;
									else
										if (flag == 9 && ch == '\\')
											flag = 9;
										else
											if (flag == 9)
												flag = 4;
											else if (flag == 4 && ch == '\n')
												flag = 0;
											else
												if (flag == 0 && ch == '\'')
													flag = 5;
												else
													if (flag == 5 && ch == '\\')
														flag = 6;
													else
														if (flag == 6)
															flag = 5;
														else
															if (flag == 5 && ch == '\'')
																flag = 0;
															else
																if (flag == 0 && ch == '\"')
																	flag = 7;
																else
																	if (flag == 7 && ch == '\\')
																		flag = 8;
																	else if (flag == 8)
																		flag = 7;
																	else
																		if (flag == 7 && ch == '\"')
																			flag = 0;
																	if ((flag == 0 && ch != '/') || flag == 5 || flag == 6 || flag == 7 || flag == 8)
																		out += ch;
																	return out;
	}
	inline bool che8(char ch)
	{
		if (ch >= '0' && ch <= '7')
			return true;
		else
			return false;
	}

	inline bool che16(char ch)
	{
		if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') ||
			(ch >= 'a' && ch <= 'f'))
			return true;
		else
			return false;
	}

	inline char get8()
	{
		int ans = 0;
		for (int i = 0; i < cou; ++i)
		{
			ans += (ren[i] - '0')*(1 << (3 * (cou - 1 - i)));
		}
		//cout << ans << endl; 
		return ans;
	}

	inline int redo(char ch)
	{
		if ((ch >= '0' && ch <= '9'))
		{
			return ch - '0';
		}
		if (ch >= 'A' && ch <= 'F')
			return ch - 'A' + 10;
		if (ch >= 'a' && ch <= 'f')
			return ch - 'a' + 10;
		return -1;
	}

	inline int get16()
	{
		int ans = 0;
		for (int i = 0; i < cou; ++i)
		{
			ans += redo(ren[i])*(1 << (4 * (cou - 1 - i)));
		}
		//cout << ans << endl;
		return ans;
	}

	inline string filstr(string &st)
	{
		string out;
		for (int i = 0; i < st.length(); ++i)
		{
			char ch = st[i];
			if (fstr == 0)
			{
				if (ch == '\'')
					fstr = 1;
				else
					if (ch == '\"')
						fstr = 2;
			}
			else
			{
				if (fstr == 1)
				{
					if (ch == '\'')
						fstr = 0;
					else
					{
						if (ch == '\\')
							fstr = 3;
					}
				}
				else
				{
					if (fstr == 2)
					{
						if (ch == '\"')
							fstr = 0;
						else
						{
							if (ch == '\\')
								fstr = 4;
						}
					}
					else
					{
						if (fstr == 3 || fstr == 4)
						{
							if (ch == 'a')
							{
								fstr /= 2;
								out += '\a';
								continue;
							}
							if (ch == 'b')
							{
								fstr /= 2;
								out += '\b';
								continue;
							}
							if (ch == 'f')
							{
								fstr /= 2;
								out += '\f';
								continue;
							}

							if (ch == 'n')
							{
								fstr /= 2;
								out += '\n';
								continue;
							}
							if (ch == 'r')
							{
								fstr /= 2;
								out += '\r';
								continue;
							}

							if (ch == 't')
							{
								fstr /= 2;
								out += '\t';
								continue;
							}

							if (ch == 'v')
							{
								fstr /= 2;
								out += '\v';
								continue;
							}
							if (ch == '\\')
							{
								fstr /= 2;
								out += '\\';
								continue;
							}
							if (ch == '\'')
							{
								fstr /= 2;
								out += '\'';
								continue;
							}
							if (ch == '"')
							{
								fstr /= 2;
								out += '\"';
								continue;
							}
							if (ch == '\n')
							{
								fstr /= 2;
								out += '\t';
								continue;
							}
							if (ch == 'x')
							{
								fstr += 2;
								cou = 0;
							}
							if (ch == '0')
							{
								fstr += 4;
								cou = 0;
							}
						}
						else
						{
							if (fstr == 5 || fstr == 6)
							{
								if (che16(ch) && cou <2)
								{
									ren[cou++] = ch;
								}
								else
								{
									fstr = (fstr - 2) / 2;
									if (cou > 0)
									{
										out += get16();
										continue;
									}
									else
									{
									//	out += '\0';
										continue;
									}
								}
								if (cou == 2)
								{
									fstr = (fstr - 2) / 2;
									out += get16();
									continue;
								}
							}
							if (fstr == 7 || fstr == 8)
							{
								if (che8(ch) && cou <2)
								{
									ren[cou++] = ch;
								}
								else
								{
									fstr = (fstr - 4) / 2;
									if (cou > 0)
									{
										out += get8();
										continue;
									}
									else
									{
									//	out += '\0';
										continue;
									}
								}
								if (cou == 2)
								{
									fstr = (fstr - 4) / 2;
									out += get8();
									continue;
								}

							}
						}
					}
				}
			}

			if (fstr == 0 || fstr == 1 || fstr == 2)
			{
				out += ch;
				continue;
			}
			else
			{
			//	out += '\0';
				continue;
			}
		}
		return out;
	}
	int line = 0;
	string name;
public:
	Input()
	{
		 fstr = flag = 0;
		 vis.clear();
	}

	inline int addfli(string &na)
	{
		Inp_rem tem;
		tem.name = na; tem.ft = fopen(na.c_str(), "r");
		if (tem.ft == NULL)
		{
			fprintf(stderr, "File: %s not found!\n",na.c_str());
			//ero.Error(1);
			return 0;
		}
		filnam.push(tem);
		return 1;
	}

	inline string getch()
	{
		string ai;
		while (true)
		{
			char now;
			while (!filnam.empty() && feof(filnam.top().ft))
			{
				fclose(filnam.top().ft);
				filnam.pop();
			}
			if (!filnam.empty())
			{
				now = getc(filnam.top().ft);
				if (now < 0) continue;
				if (now == '\n')
					++filnam.top().lin;
				line = filnam.top().lin;
				name = filnam.top().name;
				ai = del_work(now);
				if (!ai.empty())
				{
					ai = filstr(ai);
					return ai;
				}
			}
			else
			{
				ai.clear();
				return ai;
			}
		}
	}

	inline string regetch()
	{
		string ai;
		while (true)
		{
			char now;
			while (!filnam.empty() && feof(filnam.top().ft))
			{
				fclose(filnam.top().ft);
				filnam.pop();
			}
			if (!filnam.empty())
			{
				now = getc(filnam.top().ft);
				if (now < 0) continue;
				if (now == '\n')
					++filnam.top().lin;
				line = filnam.top().lin;
				name = filnam.top().name;
				ai = del_work(now);
				if (!ai.empty())
				{
					//ai = filstr(ai);
					return ai;
				}
			}
			else
			{
				ai.clear();
				return ai;
			}
		}
	}

	inline bool ifend()
	{
		return filnam.empty();
	}

	inline void include(string &na)
	{
		if (!vis.count(na))
		{
			addfli(na);
			vis.insert(na);
		}
	}

	inline void adderr(err &er)
	{
		ero = er;
	}
	inline string getle()
	{
		string le;// = "\"";
		char tst[55];
		sprintf(tst, "%d", line);
		string tem(tst);
		le += tem ;
		return le;
	}

	inline string getnam()
	{
		string nam = "\"";
		nam = nam + name + '\"';
		return nam;
	}
};

#endif