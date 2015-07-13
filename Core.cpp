#include"reg.h"
#include"Input.h"
#include"anafunc.h"
#include"err.h"

using namespace std;

class output
{
public:
	inline void putch(char ch)
	{
		putchar(ch);
	}
};


inline void about()
{
	fprintf(stderr, "=========================================================\n");
	fprintf(stderr, "JCC : A c preprocessor\n");
	fprintf(stderr, "Version: new 1.0 \n");
	fprintf(stderr, "Designed By Jia Jia\n");
	fprintf(stderr, "=========================================================\n");
	fprintf(stderr, "There will be a temp file called JCC.tem during the process!\n Please do not delete it^-^\n\n\n");
}

int main()
{
	about();
	err error;
	while (true)
	{
		string com;
		fprintf(stderr,"Input Y to continue, Input E to exit:\n");
		getline(cin, com);
		if (!(com == "Y" || com == "E"))
		{
			fprintf(stderr, "Command Error Please input again!:\n");
			continue;
		}
		else
			if (com == "E") break;
		fprintf(stderr, "请输入目标文件名：\n");
		string name;
		getline(cin, name);
		fprintf(stderr, "请输入输出文件名：\n");
		string naout;
		getline(cin, naout);
		fprintf(stderr, "Processing...\n");
		freopen("JCC.tem", "w", stdout);
		Input now;
		now.adderr(error);
		now.addfli(name);
		reg load;
		load.set_input(now);
		load.work();
		name = "JCC.tem";
		func redo;
		Input tes;
		tes.addfli(name);
		redo.setInput(tes);
		freopen(naout.c_str(), "w", stdout);
		redo.work();
		freopen("CON", "w", stdout);
		fprintf(stderr, "Build succeeded ! 0 skipped\n");
	}
	return 0;
}