/*
 * CSc103 Project 3: unix utilities
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 
 */

#include <string>
using std::string;
#include <set>
using std::set;
#include <getopt.h> // to parse long arguments.
#include <cstdio> // printf
#include <iostream>
using std::cout; 
using std::cin; 
using std::endl;
#include<vector>
using std::vector;
#include <map>
using std::map;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Limited clone of wc.  Supported options:\n\n"
"   -c,--bytes            print byte count.\n"
"   -l,--lines            print line count.\n"
"   -w,--words            print word count.\n"
"   -L,--max-line-length  print length of longest line.\n"
"   -u,--uwords           print unique word count.\n"
"   --help          show this message and exit.\n";

int char_count();

int line_count();

int word_count();

int longest_line();

int unique_count();

vector<string> for_lines();

vector<char> for_chars();

vector<char> globalinpchar;

vector<string> globalinpline;

int main(int argc, char *argv[])
{
	// define long options
	static int charonly=0, linesonly=0, wordsonly=0, uwordsonly=0, longonly=0;
	static struct option long_opts[] = {
		{"bytes",           no_argument,   0, 'c'},
		{"lines",           no_argument,   0, 'l'},
		{"words",           no_argument,   0, 'w'},
		{"uwords",          no_argument,   0, 'u'},
		{"max-line-length", no_argument,   0, 'L'},
		{"help",            no_argument,   0, 'h'},
		{0,0,0,0}
	};
	// process options:
	int opt_index = 0;
	char c;
	while ((c = getopt_long(argc, argv, "clwuLh", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'c':
				charonly = 1;
				break;
			case 'l':
				linesonly = 1;
				break;
			case 'w':
				wordsonly = 1;
				break;
			case 'u':
				uwordsonly = 1;
				break;
			case 'L':
				longonly = 1;
				break;
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}
	/* TODO: write me... */
	for_chars();	
	if(linesonly == 1)
	{
		line_count();
	}
	if(wordsonly == 1)
	{
		word_count();
	}
	if(charonly == 1)
	{
		char_count();
	}
	if(longonly == 1)
	{
		longest_line();
	}
	if(uwordsonly == 1)
	{
		unique_count();
	}
	if(linesonly==0&&wordsonly==0&&charonly==0&&longonly==0&&uwordsonly==0)
	{
		line_count();
		word_count();
		char_count();
	}
	cout << endl;
	return 0;
}

vector<char> for_chars()
{
	char c;
	while(fread(&c,1,1,stdin))
	{
		globalinpchar.push_back(c);
	}
	return globalinpchar;
}

int char_count()
{
	cout << '\t' << globalinpchar.size();
	return 0;
}

int line_count()
{
	int linecount = 0;
	string inp;
	for(unsigned i = 0; i < globalinpchar.size()-1; i++)
	{
		if(globalinpchar[i] == '\n')
		{
			linecount++;
		}
	}
	if(globalinpchar[globalinpchar.size()-1] == '\n')
	{
		linecount++;
	}
	cout << '\t' << linecount;
	return 0;
}

int word_count()
{
	int wordcount = 0;
	char prev;
	char curr;
	vector<char> inp;
	if(globalinpchar[0] == ' ' || globalinpchar[0] == '\t')
	{
		for(unsigned i = 1; i < globalinpchar.size(); i++)
		{
			curr = globalinpchar[i];
			prev = globalinpchar[i-1];
			if((curr==' '||curr=='\t'||curr=='\n') && (prev!=' '&&prev!='\t'&&prev!='\n'))
			{
				cout << "";
				wordcount++;
			}
		}
	}
	else
	{
		for(unsigned i = 1; i < globalinpchar.size(); i++)
		{
			curr = globalinpchar[i];
			prev = globalinpchar[i-1];
			if((curr==' '||curr=='\t'||curr=='\n') && (prev!=' '&&prev!='\t'&&prev!='\n'))
			{
				cout << "";
				wordcount++;
			}
		}
	}
	if((globalinpchar[globalinpchar.size()-1]!=' ')&&(globalinpchar[globalinpchar.size()-1]!='\t')&&(globalinpchar[globalinpchar.size()-1]!='\n'))
	{
		wordcount++;
	}
	cout << '\t' << wordcount;
	return 0;
}

int longest_line()
{
	vector<vector<char> > bigvector;
	string inp;
	vector<char> stuff;
	unsigned max_length = 0;
	vector<char> tmp;	
	for(unsigned k = 0; k < globalinpchar.size()-1; k++)
	{
		tmp.push_back(globalinpchar[k]);
		if(globalinpchar[k] == '\n')
		{
			bigvector.push_back(tmp);
			tmp.clear();
		}
	}
	for(unsigned i = 0; i < bigvector.size(); i++)
	{
		unsigned length = 0;
		vector<char> currline = bigvector[i];
		for(unsigned j = 0; j < currline.size(); j++)
		{
			if(currline[j] == '\t')
			{
				length += 8 - length%8;
			}
			else
			{
				length++;
			}
		}
		if(length > max_length)
		{
			max_length = length;
		}
	}
	cout << '\t' << max_length - 1;
	return 0;
}

int unique_count()
{
	set<vector<char> > words;
	vector<vector<char> > bigvector;
	string inp;
	vector<char> stuff;
	vector<char> tmp;	
	char curr;
	char prev;
	for(unsigned k = 0; k < globalinpchar.size()-1; k++)
	{
		tmp.push_back(globalinpchar[k]);
		curr = globalinpchar[k];
		prev = globalinpchar[k-1];
		if((curr==' '||curr=='\t'||curr=='\n') && (prev!=' '&&prev!='\t'&&prev!='\n'))
		{
			cout << "";
			bigvector.push_back(tmp);
			tmp.clear();
		}
	}
	for(unsigned i = 0; i < bigvector.size(); i++)
	{
		vector<char> word = bigvector[i]; 
		words.insert(word);
	}
	cout << '\t' << words.size();
	return 0; 
}
