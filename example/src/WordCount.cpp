/************************************************************
 FileName: WordCount.cpp
 Author:Zou Pufan Version:7.0 Date:2021/2/27
 Description: // ģ������
 Version: // �汾��Ϣ
 Function List: // ��Ҫ�������书��
 1. -------
 History: // ��ʷ�޸ļ�¼
 <author> <time> <version > <desc>
 David 96/10/12 1.0 build this moudle
***********************************************************/
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
	int Countchar(fstream& in,string outputFileName);
	int Countword(fstream& in, string outputFileName);
	int Countline(fstream& in, string outputFileName);
	/*bool sortWordTimes(const word&a, const word &b);*/
	void Countwordoccurtimes(fstream& in,string outputFileName);
	
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
	string Getword()
	{
		return this->wordToFind;
	}
	bool operator()(word& nWord)//�ж��Ƿ񼯺�������ȵĵ�������Ϊfind_if���ԱȽϺ�����
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
/*************************************************
 Description:��Ϊvector�������Զ���ıȽϺ����Ƚ�vector�����е�word��Ԫ�أ����ȸ��ݵ��ʳ��ִ������бȽϣ�������ٸ����ֵ�������
 Input: �������Ϊ�������ԱȽϵ�word�ೣ������ϵΪ��Ϊ�����е�Ԫ���Խ��бȽϡ�// �������˵��������ÿ����������
 // �á�ȡֵ˵�����������ϵ��
 Output: �����ֵ// �����������˵����
 Return:�ж�����word��Ԫ��֮���С��boolֵ // ��������ֵ��˵��
 Others: // ����˵��
*************************************************/
bool Sortwordtimes(const word &wordA, const word &wordB)
{
	if (wordA.occurCount == wordB.occurCount)
	{
		return wordA.wordName < wordB.wordName;//�жϵ��ʵ��ֵ���
	}
	else
	{
		return wordA.occurCount > wordB.occurCount;
	}

}
/*************************************************
 Description:ͨ��vector�����ĵ�������������������õ��ʳ��ֵĴ���ǰʮ�ߵĵ���������ִ���д������ļ���
 Input: ��������ֱ�Ϊfstream�������in�������ļ��Ķ�ȡ����string��outputFilename����д������ļ����ļ���// �������˵��������ÿ����������
 // �á�ȡֵ˵�����������ϵ��
 Output: ���ֵΪ�����output�ļ��ĵ������뵥�ʳ��ִ���// �����������˵����
 Return:��returnֵ // ��������ֵ��˵��
 Others: // ����˵��
*************************************************/
void myfile::Countwordoccurtimes(fstream&in, string outputFileName)
{
	fstream out;
	out.open(outputFileName.c_str(),ios::app);
	sort(this->wVector.begin(), this->wVector.end(),Sortwordtimes);//�����Զ��庯��Sortwordtimes��vector������������
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
/*************************************************
 Description:ͨ����������ļ����������ַ��Ķ�ȡ�Լ����ַ�����
 Input: ��������ֱ�Ϊfstream�������in�������ļ��Ķ�ȡ����string��outputFilename����д������ļ����ļ���// �������˵��������ÿ����������
 // �á�ȡֵ˵�����������ϵ��
 Output: ���ֵΪ�����output�ļ����ַ����ִ���// �����������˵����
 Return:��returnֵ // ��������ֵ��˵��
 Others: // ����˵��
*************************************************/
int myfile::Countchar(fstream &in, string outputFileName)
{
	fstream out;
	out.open(outputFileName.c_str(),ios::app);
	int totalCount=0;
	char temp;
   in>>noskipws;//���ò��������з��Ϳհ׷�
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
/*************************************************
 Description:ͨ����������ļ����������ַ��Ķ�ȡ������ȡ�����ַ�ƴ��Ϊ�ַ������������ָ������ǰƴ�ӳɵ��ַ������м�飬�ж��Ƿ�Ϊ��Ч�ĵ��ʣ�����Ч�����vector�����С���Ч��������
 Input: ��������ֱ�Ϊfstream�������in�������ļ��Ķ�ȡ����string��outputFilename����д������ļ����ļ���// �������˵��������ÿ����������
 // �á�ȡֵ˵�����������ϵ��
 Output: ���ֵΪ�����output�ļ��ĵ����ܼƳ��ִ���// �����������˵����
 Return:��returnֵ // ��������ֵ��˵��
 Others: // ����˵��
*************************************************/
int myfile::Countword(fstream &in, string outputFileName)
{
	bool isWord = true;//�ж��ַ��������Ƿ���ϵ������
	fstream out;
	out.open(outputFileName.c_str(),ios::app);
	in.unsetf(ios_base::skipws);//���ò��������з��Ϳհ׷�
	if (!in.is_open())
	{
		cout << "�޷����ļ�" << endl;
		exit(0);
	}
	int totalCount = 0;
	string wordString = "";
	char temp;
   in>>noskipws;
   if(in.eof())
   {
   	cout<<"�ļ�����ĩβ"<<endl;
   }
   while(!in.eof())
   {

   	in>>temp;
	if (temp <= 'Z'&&temp >= 'A')//����ַ�Ϊ��д��ĸ����ת��ΪСд��ĸ
	{
		temp += 32;
	}
	if (temp <= 32 || temp>126||temp=='\n')//�ж��Ƿ������ָ��������ִ����������
	{
		if (wordString.length() < 4)//������ʳ���С��4����ֱ������������ַ�������
		{
			wordString = "";
			continue;
		}
		for (int i = 0;i < 4;i++)
		{
			if (!isalpha(wordString[i]))//�ж��ַ���ǰ��λ�Ƿ�Ϊ��ĸ����Ϊ��ĸ��ֱ�ӽ���ѭ��
			{
				wordString = "";
				isWord = false;
				break;
			}

		}
		if (!isWord)//�����Ϊ���������ִ����һ��whileѭ������ִ�����´���
		{
			isWord = true;
			continue;
		}
		totalCount++;

		//ͨ��find_if��������Զ����findword�����жϵ����Ƿ���vector�����г��ֹ��������ֹ�����ӵ��ʴ������ɣ�δ���ֹ�������µ�Ԫ�ء�
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
   if (!wordString.empty())//���ļ���ȡ������û�������ָ���ȴ�ַ�����ȴ�������ݣ�Ҫ�������һ�μ�顣
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
   out << "word:" << totalCount << endl;//������ʵ�����
   out.close();
   out.clear();
	return totalCount;
}
/*************************************************
 Description:ͨ����������ļ����������еĶ�ȡ��ͳ���ļ�������
 Input: ��������ֱ�Ϊfstream�������in�������ļ��Ķ�ȡ����string��outputFilename����д������ļ����ļ���// �������˵��������ÿ����������
 // �á�ȡֵ˵�����������ϵ��
 Output: ���ֵΪ�����output�ļ���input�ļ����ܹ���������// �����������˵����
 Return:��returnֵ // ��������ֵ��˵��
 Others: // ����˵��
*************************************************/
int myfile::Countline(fstream &in, string outputFileName)
{
	fstream out;
	out.open(outputFileName.c_str(),ios::app);
	if (!in.is_open())
	{
		cout << "�޷����ļ�" << endl;
		exit(0);
	}
	int totalCount = 0;
	string line;
	while (!in.eof())
	{
		getline(in,line);
		for (int i = 0;i < line.length();i++)
		{
			if (!isspace(line[i]))//���ļ��������еĶ�ȡ���ж��Ƿ���ڷǿհ��ַ���
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
		cout << "�޷����ļ�" << endl;
		exit(0);
	}
	mf->Countchar(in, "C:/Users/puffer/Desktop/learngit/221801231/example/src/output.txt");
	in.close();
	in.clear();
	in.open("C:/Users/puffer/Desktop/learngit/221801231/example/src/input.txt");
	mf->Countword(in, "C:/Users/puffer/Desktop/learngit/221801231/example/src/output.txt");
	in.close();
	in.clear();
	in.open("C:/Users/puffer/Desktop/learngit/221801231/example/src/input.txt");
	mf->Countline(in, "C:/Users/puffer/Desktop/learngit/221801231/example/src/output.txt");
	in.close();
	in.clear();
	in.open("C:/Users/puffer/Desktop/learngit/221801231/example/src/input.txt");
	mf->Countwordoccurtimes(in, "C:/Users/puffer/Desktop/learngit/221801231/example/src/output.txt");
	in.close();
	in.clear();
}
