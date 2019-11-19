#include<fstream>
#include<sstream>
#include<iostream>

#include"chainWithBinsort.h"
using namespace std;
const int TEMP_AND_NUM_LENGTH = 10;
int main()
{
	const char* c;
	ifstream input("DataFile.df");
	stringstream ss;
	string inputString;
	ss << input.rdbuf();
	input.close();
	inputString = ss.str();
	c = inputString.c_str();
	chain<int> test;
	for (unsigned i = 0; i < inputString.length(); i++)
	{
		char tempC[TEMP_AND_NUM_LENGTH];
		int num;
		for (int j=0; j < TEMP_AND_NUM_LENGTH; j++)
		{//截断空格前的一个数字
			if (c[i] == ' '||c[i]=='\n')
			{
				tempC[j] = '\0';
				break;
			}
			tempC[j] = c[i++];
		}
		if (tempC[0] == '\0')
			continue;
		sscanf_s(tempC, "%d", &num);//将字符串转化为数字
		test.insert(0, num);
	}
	test.binsort(101);
	test.output(cout);
	return 0;
}