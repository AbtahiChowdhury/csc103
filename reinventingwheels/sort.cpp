//NAME: PHUC NGUYEN
//ID: 23282745

#include <strings.h>
#include <string.h>
#include <iostream>
#include <cstdio>
#include <getopt.h> // to parse long arguments.
#include <string>
#include <set>
#include <stdio.h>
using namespace std;
using std::string;
using std::cin;
using std::cout;

using std::set;
using std::multiset;


static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Limited clone of sort.  Supported options:\n\n"
"   -r,--reverse        Sort descending.\n"
"   -f,--ignore-case    Ignore case.\n"
"   -u,--unique         Don't output duplicate lines.\n"
"   --help              Show this message and exit.\n";

struct igncaseComp {
	bool operator()(const string& s1, const string& s2) {
		return (strcasecmp(s1.c_str(),s2.c_str()) < 0);
	}
};
/* NOTE: set<string,igncaseComp> S; would declare a set S which
 * does its sorting in a case-insensitive way! */
int comparestring(string a,string b);
int main(int argc, char *argv[]) {
	// define long options
	static int descending=0, ignorecase=0, unique=0;
	static struct option long_opts[] = {
		{"reverse",       no_argument,   0, 'r'},
		{"ignore-case",   no_argument,   0, 'f'},
		{"unique",        no_argument,   0, 'u'},
		{"help",          no_argument,   0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "rfuh", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'r':
				descending = 1;
				break;
			case 'f':
				ignorecase = 1;
				break;
			case 'u':
				unique = 1;
				break;
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}
	//////////////// DECLARE VARIABLE//////////////////
	int count, numword;
	string word[1000];
	string temp;
///////////////////////TAKE INPUT/////////////////////
	while(getline(cin, temp))
		{
			word[count] = temp;
			count++; //cout how many inputs
		}
		numword = count;

	////////////////////// -r -u -f ////////////////////////
	if (descending == 1 && ignorecase==1 && unique==1)
	{
		for (int i=0;i<numword;i++)
		{
			for(int j=0;j<numword;j++)
			{
				if (comparestring(word[i],word[j])>0)
				{
					temp = word[i];
					word[i] = word[j];
					word[j] =temp;
				}
			}
		}
		for (int i=0;i<numword;i++)
		{
			if(word[i] != word[i+1])
			{cout<<word[i]<<endl;}
		}
	}
	///////////////////// -r -u ///////////////
	else if (descending == 1 && unique==1)
	{
		for (int i=0;i<numword;i++)
		{
			for(int j=0;j<numword;j++)
			{
				if (word[i]>word[j]) //Compare between 2 strings and Swap
				{
					//cout <<word[i]<<" < "<<word[j]<<endl;
					temp = word[i];
					word[i] = word[j];
					word[j] =temp;
				}
			}
		}
		//cout << "\nAfter sort: "<<endl;
		for (int i=0;i<numword;i++)
		{
			if(word[i] != word[i+1])
			{cout<<word[i]<<endl;}
		}
	}
	//////////////////////// -r -f //////////////
	else if (descending == 1 && ignorecase==1) //////////////ERRO???????????
	{
		for (int i=0;i<numword;i++)
		{
			for(int j=0;j<numword;j++)
			{
				if (comparestring(word[i],word[j])>0)
				{
					temp = word[i];
					word[i] = word[j];
					word[j] =temp;
				}
			}
		}
		for (int i=0;i<numword;i++)
		{
			cout<<word[i]<<endl;
		}
	}
	///////////////////// -u -f /////////////////
	else if (unique == 1 && ignorecase==1)
	{
		for (int i=0;i<numword;i++)
		{
			for(int j=0;j<numword;j++)
			{
				if (comparestring(word[i],word[j])<0)
				{
					temp = word[i];
					word[i] = word[j];
					word[j] =temp;
				}
			}
		}
		for (int i=0;i<numword;i++)
		{
			if(word[i] != word[i+1])
			{cout<<word[i]<<endl;}
		}
	}
	///////////////////// -r /////////////////
	else if (descending ==1)
	{
		for (int i=0;i<numword;i++)
		{
			for(int j=0;j<numword;j++)
			{
				if (word[i]>word[j]) //Compare between 2 strings and Swap
				{
					temp = word[i];
					word[i] = word[j];
					word[j] =temp;
				}
			}
		}
		for (int i=0;i<numword;i++)
		{
			cout <<word[i]<<endl;
		}
	}
	///////////////////// -u /////////////////
	else if (unique ==1)
	{
		for (int i=0;i<numword;i++)
		{
			for(int j=0;j<numword;j++)
			{
				if (word[i]<word[j]) //Compare between 2 strings and Swap
				{
					temp = word[i];
					word[i] = word[j];
					word[j] =temp;
				}
			}
		}
		for (int i=0;i<numword;i++)
		{
			if(word[i] != word[i+1])
			{cout<<word[i]<<endl;}
		}
	}
	///////////////////// -f /////////////////
	else if (ignorecase ==1)
	{
		for (int i=0;i<numword;i++)
		{
			for(int j=0;j<numword;j++)
			{
				if (comparestring(word[i],word[j])<0)
				{
					temp = word[i];
					word[i] = word[j];
					word[j] =temp;
				}
			}
		}
		for (int i=0;i<numword;i++)
		{
			cout<<word[i]<<endl;
		}
	}
	////////////////////// sort //////////////////////
	if(descending != 1 && ignorecase != 1 && unique != 1)
	{
		for (int i=0;i<numword;i++)
		{
			for(int j=0;j<numword;j++)
			{
				if (word[i]<word[j]) //Compare between 2 strings and Swap
				{
					//cout <<word[i]<<" < "<<word[j]<<endl;
					temp = word[i];
					word[i] = word[j];
					word[j] =temp;
				}
			}
		}
			//cout << "\nAfter sort: "<<endl;

		for (int i=0;i<numword;i++)
		{
			cout <<word[i]<<endl;
		}
	}
	return 0;
}
int comparestring(string a,string b)
{
	int t;
	char temp1[a.size()+1],temp2[b.size()+1];
	strcpy (temp1,a.c_str());
	strcpy (temp2,b.c_str());
	//strcpy (temp2,b.c_str(),sizeof(temp2));
	//cout <<temp1<<endl<<temp2<<endl;
	t=strcasecmp(temp1,temp2);
	//cout << temp1<<endl;
	//cout << temp2<<endl;
	//cout <<t<<endl;
	return t;
}



//////	USING SET FOR UNIQ////////////
/*
set <string>::iterator i; // pointer
		string word;
		set <string> B; //set
		while(cin>>word)
		{
			B.insert(word); //only insert if element is not in the set -- not duplicate
			//cout << word<<endl;
			//cout << word.size()<<endl;
			//cout << word.length()<<endl;
		}
		for (i=begin(B);i!=end(B);i++) // sort using iterator pointer of the set
		{
			cout<<*i<<endl;
		}
*/
