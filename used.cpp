//#include"Input.h"
//# include<regex>
//#include<set>
//using namespace std;
//int main()
//{
//	int n;
//	cin >> n;
//	Input now;
//	for (int i = 1; i <= n; ++i)
//	{
//		string name;
//		cin >> name;
//		now.addfli(name);
//	}
//	string st;
//
//	string tem = "(#\s*?include)(\s*?)(\"|<)(\s*?)(.+?)(\s*?)(\"|>)";
//	string te = "(#\\s*?include\\s*)(\"|<)(\\s*)(.+?)(\\s*)(\"|>)";
//	string te1 = "(#\\s*define\\s+)(\\w+)(\\s*)$";
//	string te2 = "(#\\s*define\\s+)(\\w+)(\\s+)(.+)(\\s*)$";
//	string te3 = "(#\\s*define\\s+)(\\w+?)\\((.+?)\\)(\\s+)(.+?)(\\s*)$";
//	string fmt = "$2 $3 $5";
//	string fe = "(.*?)(__LINE__)(.*?)$";
//	string fe1 = "(.*?)(__FILE__)(.*?)$";
//	string he1 = "(#\\s*ifdef\\s+)(\\w+?)(\\s*)$";
//	string he2 = "(#\\s*ifndef\\s+)(\\w+?)(\\s*)$";
//	string he3 = "(#\\s*undef\\s+)(\\w+?)(\\s*)$";
//	string he = "(#\\s*undef\\s+)(\\w+?)(\\s*)$";
//	string fe3 = "__LINE__";
//	regex pat(te2);
//	smatch ans;
//	char temc;
//	while (!now.ifend())
//	{
//		while (!now.ifend())
//		{
//			temc = now.getch();
//			if (temc > 0)
//				st += temc;
//			//putchar(temc);
//			//cout << st << endl;
//			if (temc == '\n') break;
//		}
//		//cout << now.getle();
//		//cout << st;
//		int fla = 0;
//		//fmt = "";
//		//st = regex_replace(st, pat, fmt90
//		cout << st;
//		for (sregex_iterator it(st.begin(), st.end(), pat), endi; it != endi; ++it)
//		{
//			cout << it->str() << endl;
//			//	fmt.clear();
//			fmt = "$2  $4";
//			cout << regex_replace(it->str(), pat, fmt)<<endl;
//			//include (now,regex_replace(it->str(), pat, fmt)) ;
//			//fla = 1;
//		}
//		//if (!fla) cout << st;
//		st.clear();
//	}
//	/*while (!now.ifend())
//	{
//	putchar(now.getch());
//	}*/
//	return 0;
//}