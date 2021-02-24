#include<iostream>
#include<fstream>
#include<string>
#define MAX_NUM 1024
using namespace std;
int charCount(File *file)
{
	char buf[MAX_NUM];
	int totalCount,len=0;
	while (!feof(file)&&!ferror(file))
	{
		fgets(buf, MAX_NUM, file);
		len = strlen(buf);
		if (len == 0)
		{
			continue;
		}
		totalCount += len;
	}
	cout << "characters:" << totalCount << endl;
}
int main()
{
	string inputFileName = "";
	string outputFileName = "";
	cin >> inputFileName >> outputFileName;
	File *in = fopen(inputFileName,"r");
	if (in == NULL)
	{
		cout << "无法打开文件" << endl;
		exit(0);
	}
	charCount(in);
	
}