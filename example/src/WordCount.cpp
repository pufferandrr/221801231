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
	int charCount(fstream& in);
	int wordCount(fstream& in);
//	int mostWordCount(FILE *file);
	
private:
	string fileName;
	int characterNum;
	int wordNum;
	vector<word> wVector;
};


int myFile::charCount(fstream &in)
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
int myFile::wordCount(fstream &in)
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
   	wordString=wordString+temp;
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
	myFile* mf =new myFile(inputFileName) ;

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
