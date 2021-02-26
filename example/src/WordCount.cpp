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
	int charCount(fstream& in);
	int wordCount(fstream& in);
	int lineCount(fstream& in);
	/*bool sortWordTimes(const word&a, const word &b);*/
	void wordOccurTimesCount(fstream& in);
	
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
void myfile::wordOccurTimesCount(fstream&in)
{
	sort(this->wVector.begin(), this->wVector.end(),sortWordTimes);
	vector<word>::iterator it = this->wVector.begin();
	if (this->wVector.size() <= 10)
	{
		for (int i = 0;i < this->wVector.size();i++)
		{
			cout << it->wordName << ":"<<it->occurCount << endl;
			++it;
		}
	}
	else
	{
		for (int i = 0;i < 10;i++)
		{
			cout << it->wordName << ":" << it->occurCount << endl;
			++it;
		}
	}
	
}

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
   cout<<"characters:"<<totalCount<<endl;
	return totalCount;
}
int myfile::wordCount(fstream &in)
{
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
				continue;
			}

		}
		for (int j = 0;j < wordString.length();j++)
		{

			if (wordString[j] <= 'Z'&&wordString[j] >= 'A')
			{
				wordString[j] += 32;
			}
		}
		totalCount++;
		 cout<<wordString;
		vector<word>::iterator it = find_if(this->wVector.begin(), this->wVector.end(), findword(wordString));
		if (it != this->wVector.end())
		{
			it->occurCount++;
		}
		else
		{
			this->wVector.push_back(word(wordString));
			wordString = "";
		}
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
			   break;
		   }

	   }
	   for (int j = 0;j < wordString.length();j++)
	   {

		   if (wordString[j] <= 'Z'&&wordString[j] >= 'A')
		   {
			   wordString[j] += 32;
		   }
	   }
	   totalCount++;
	   cout << wordString;
	   vector<word>::iterator it = find_if(this->wVector.begin(), this->wVector.end(), findword(wordString));
	   if (it != this->wVector.end())
	   {
		   it->occurCount++;
	   }
	   else
	   {
		   this->wVector.push_back(word(wordString));
		   wordString = "";
	   }
   }
   in.close(); 
   in.clear();
   cout << "word:" << totalCount << endl;
	return totalCount;
}
int myfile::lineCount(fstream &in)
{
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
	cout << "line:" << totalCount << endl;
}
int main()
{
	
	string inputFileName = "";
	string outputFileName = "";
	cin >> inputFileName; 
	myfile* mf =new myfile(inputFileName) ;

fstream in;
in.open("C:/Users/puffer/Desktop/learngit/221801231/example/src/test.txt");
	if (!in.is_open())
	{
		cout << "无法打开文件" << endl;
		exit(0);
	}
	mf->charCount(in);
	in.close();
	in.clear();
	in.open("C:/Users/puffer/Desktop/learngit/221801231/example/src/test.txt");
	mf->wordCount(in);
	in.close();
	in.clear();
	in.open("C:/Users/puffer/Desktop/learngit/221801231/example/src/test.txt");
	mf->lineCount(in);
	in.close();
	in.clear();
	in.open("C:/Users/puffer/Desktop/learngit/221801231/example/src/test.txt");
	mf->wordOccurTimesCount(in);
}
