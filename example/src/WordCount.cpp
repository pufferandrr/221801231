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
	word(string wordN)
	{
		this->wordName = wordN;
		this->occurCount=1;
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
	int charCount(fstream& in,string outputFileName);
	int wordCount(fstream& in, string outputFileName);
	int lineCount(fstream& in, string outputFileName);
	/*bool sortWordTimes(const word&a, const word &b);*/
	void wordOccurTimesCount(fstream& in,string outputFileName);
	
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
bool sortWordTimes(const word &a, const word &b)
{
	if (a.occurCount == b.occurCount)
	{
		return a.wordName < b.wordName;
	}
	else
	{
		return a.occurCount > b.occurCount;
	}

}
void myfile::wordOccurTimesCount(fstream&in, string outputFileName)
{
	fstream out;
	out.open(outputFileName.c_str(),ios::app);
	sort(this->wVector.begin(), this->wVector.end(),sortWordTimes);
	vector<word>::iterator it = this->wVector.begin();
	if (this->wVector.size() <= 10)
	{
		for (int i = 0;i < this->wVector.size();i++)
		{
			out << it->wordName << ":"<<it->occurCount << '\n';
			++it;
		}
	}
	else
	{
		for (int i = 0;i < 10;i++)
		{
			out << it->wordName << ":" << it->occurCount <<'\n';
			++it;
		}
	}
	out.close();
	out.clear();
}

int myfile::charCount(fstream &in, string outputFileName)
{
	fstream out;
	out.open(outputFileName.c_str(),ios::app);
	int totalCount=0;
	char temp;
   in>>noskipws;
   in>>temp;
   while(!in.eof())
   {
   	totalCount++;
   	in>>temp;
   }
   out<<"characters:"<<totalCount<<'\n';
   out.close();
   out.clear();
	return totalCount;
}
int myfile::wordCount(fstream &in, string outputFileName)
{
	bool isWord = true;
	fstream out;
	out.open(outputFileName.c_str(),ios::app);
	in.unsetf(ios_base::skipws);
	if (!in.is_open())
	{
		cout << "无法打开文件" << endl;
		exit(0);
	}
	int totalCount = 0;
	string wordString = "";
	char temp;
   in>>noskipws;
   if(in.eof())
   {
   	cout<<"文件到达末尾"<<endl;
   }
   while(!in.eof())
   {

   	in>>temp;
	if (temp <= 'Z'&&temp >= 'A')
	{
		temp += 32;
	}
	if (temp <= 32 || temp>126||temp=='\n')
	{
		if (wordString.length() < 4)
		{
			wordString = "";
			continue;
		}
		for (int i = 0;i < 4;i++)
		{
			if (!isalpha(wordString[i]))
			{
				wordString = "";
				isWord = false;
				break;
			}

		}
		if (!isWord)
		{
			isWord = true;
			continue;
		}

		totalCount++;
		vector<word>::iterator it = find_if(this->wVector.begin(), this->wVector.end(), findword(wordString));
		if (it != this->wVector.end())
		{
			it->occurCount++;
		}
		else
		{
			this->wVector.push_back(word(wordString));
			
		}
		wordString = "";
	}
	else	wordString=wordString+temp;
   }
   if (!wordString.empty())
   {
	   if (wordString.length() < 4)
	   {
		   wordString = "";
		  
	   }
	   for (int i = 0;i <= 4;i++)
	   {
		   if (!isalpha(wordString[i]))
		   {
			   wordString = "";
			   isWord = false;
			   break;
		   }

	   }
	   if (isWord)
	   {
		   for (int j = 0;j < wordString.length();j++)
		   {

			   if (wordString[j] <= 'Z'&&wordString[j] >= 'A')
			   {
				   wordString[j] += 32;
			   }
		   }
		   totalCount++;
		   vector<word>::iterator it = find_if(this->wVector.begin(), this->wVector.end(), findword(wordString));
		   if (it != this->wVector.end())
		   {
			   it->occurCount++;

		   }
		   else
		   {
			   this->wVector.push_back(word(wordString));

		   }
		   wordString = "";
	   }
	   else
	   {
		   isWord = true;
	   }
   }
   in.close(); 
   in.clear();
   out << "word:" << totalCount << endl;
   out.close();
   out.clear();
	return totalCount;
}
int myfile::lineCount(fstream &in, string outputFileName)
{
	fstream out;
	out.open(outputFileName.c_str(),ios::app);
	if (!in.is_open())
	{
		cout << "无法打开文件" << endl;
		exit(0);
	}
	int totalCount = 0;
	string line;
	while (!in.eof())
	{
		getline(in,line);
		for (int i = 0;i < line.length();i++)
		{
			if (!isspace(line[i]))
			{
				totalCount++;
				break;
			}
		}
	}
	out << "line:" << totalCount << endl;
	out.close();
	out.clear();
	return totalCount;
}
int main(int argc, char *argv[])
{
	
	string inputFileName = "";
	string outputFileName = "";
	cin >> inputFileName>>outputFileName; 
	myfile* mf =new myfile(inputFileName) ;

fstream in;
fstream out;
in.open("C:/Users/puffer/Desktop/learngit/221801231/example/src/input.txt");
out.open("C:/Users/puffer/Desktop/learngit/221801231/example/src/output.txt",ios::out);
out.close();
out.clear();

	if (!in.is_open())
	{
		cout << "无法打开文件" << endl;
		exit(0);
	}
	mf->charCount(in, "C:/Users/puffer/Desktop/learngit/221801231/example/src/output.txt");
	in.close();
	in.clear();
	in.open("C:/Users/puffer/Desktop/learngit/221801231/example/src/input.txt");
	mf->wordCount(in, "C:/Users/puffer/Desktop/learngit/221801231/example/src/output.txt");
	in.close();
	in.clear();
	in.open("C:/Users/puffer/Desktop/learngit/221801231/example/src/input.txt");
	mf->lineCount(in, "C:/Users/puffer/Desktop/learngit/221801231/example/src/output.txt");
	in.close();
	in.clear();
	in.open("C:/Users/puffer/Desktop/learngit/221801231/example/src/input.txt");
	mf->wordOccurTimesCount(in, "C:/Users/puffer/Desktop/learngit/221801231/example/src/output.txt");
	in.close();
	in.clear();
}
