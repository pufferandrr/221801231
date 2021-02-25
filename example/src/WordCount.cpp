#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<cstring>
#include<vector>
#define MAX_NUM 1024

using namespace std;
class word
{
public:
	word()
	{
		this->occurCount = 0;
		this->wordName = "";
	}
	

private:
	int occurCount;
	string wordName;
};
class myFile
{
public:
	myFile()
	{
		this->fileName = "";
		this->characterNum = this->wordNum = 0;
	}
	myFile(string s)
	{
		this->fileName = s;
		this->characterNum = this->wordNum = 0;
	}
	int charCount(FILE *file);
	int wordCount(FILE *file);
	int mostWordCount(FILE *file);
	
private:
	string fileName;
	int characterNum;
	int wordNum;
	vector<word> wVector;
};


int myFile::charCount(FILE *file)
{
	char buf[MAX_NUM];
	int totalCount=0,len=0;
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
	fclose(file);
	return totalCount;
}
int myFile::wordCount(FILE *file)
{
	int totalCount = 0;
	string tmp = "";
	char c;
	while (!feof(file)&&!ferror(file))
	{

	}

}
int main()
{
	
	string inputFileName = "";
	string outputFileName = "";
	cin >> inputFileName; 
	FILE *in = fopen(inputFileName.c_str(),"r");
	if (in == NULL)
	{
		cout << "无法打开文件" << endl;
		exit(0);
	}
	charCount(in);
	
}
