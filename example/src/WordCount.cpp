#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<cstring>
#include<vector>
#include<algorithm>
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
	


	int occurCount;
	string wordName;
};
class myfile
{
public:
	myfile()
	{
		this->fileName = "";
		this->characterNum = this->wordNum = 0;
	}
	myfile(string s)
	{
		this->fileName = s;
		this->characterNum = this->wordNum = 0;
	}
	int charCount(fstream& in);
	int wordCount(fstream& in);
//	int mostWordCount(FILE *file);
	
private:
	string fileName;
	int characterNum;
	int wordNum;
	vector<word> wVector;
};
class findword
{
public:
	findword(const string str)
	{
		this->wordToFind = str;
	}
	string GetWord()
	{
		return this->wordToFind;
	}
	bool operator()(word& nWord)
	{
		if (nWord.wordName == this->wordToFind)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	string wordToFind;
};
int myfile::charCount(fstream &in)
{
	int totalCount=0;
	char temp;
   in>>noskipws;
   in>>temp;
   while(!in.eof())
   {
   	totalCount++;
   	in>>temp;
   }
   cout<<"characters:"<<totalCount;
	return totalCount;
}
int myfile::wordCount(fstream &in)
{

	if (!in.is_open())
	{
		cout << "无法打开文件" << endl;
		exit(0);
	}
	int totalCount = 0;
	string wordString = "";
	char temp;
   in>>noskipws;
   in>>temp;
   if(in.eof())
   {
   	cout<<"文件到达末尾"<<endl;
   }
   while(!in.eof())
   {
   	in>>temp;
	if (temp <= 32 || temp>126)
	{
		for (int i = 0;i <= 4;i++)
		{
			if (!isalpha(wordString[i]))
			{
				wordString = "";
				continue;
			}

		}
		vector<word>::iterator it = find_if(this->wVector.begin(), this->wVector.end(), findword(wordString));
	}
	else	wordString=wordString+temp;
   }
   cout<<wordString;
   in.close(); 
   in.clear();

	return totalCount;
}
int main()
{
	
	string inputFileName = "";
	string outputFileName = "";
	cin >> inputFileName; 
	myfile* mf =new myfile(inputFileName) ;

fstream in;
in.open(inputFileName.c_str());
	if (!in.is_open())
	{
		cout << "无法打开文件" << endl;
		exit(0);
	}
	mf->charCount(in);
	in.close();
	in.clear();
	in.open(inputFileName.c_str());
	mf->wordCount(in);
	
}
