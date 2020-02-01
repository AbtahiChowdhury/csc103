#include <cstdio>
#include <getopt.h> // to parse long arguments.
#include <string>
using std::string;
#include <iostream>
#include <stdio.h>
using std::cin;
using std::cout;
using std::endl;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Limited clone of uniq.  Supported options:\n\n"
"   -c,--count         prefix lines by their counts.\n"
"   -d,--repeated      only print duplicate lines.\n"
"   -u,--unique        only print lines that are unique.\n"
"   --help             show this message and exit.\n";

int main(int argc, char *argv[]) {
	// define long options
	static int showcount=0, dupsonly=0, uniqonly=0;
	static struct option long_opts[] = {
		{"count",         no_argument, 0, 'c'},
		{"repeated",      no_argument, 0, 'd'},
		{"unique",        no_argument, 0, 'u'},
		{"help",          no_argument, 0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "cduh", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'c':
				showcount = 1;
				break;
			case 'd':
				dupsonly = 1;
				break;
			case 'u':
				uniqonly = 1;
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

	if (showcount==1)
	{

		if (dupsonly==1)
		{
			if(uniqonly==1)
			{
				return 0;
			}
			size_t count=1;
			string thisLine, previousLine;
			getline(cin, previousLine);
			getline(cin, thisLine);
			do
			{
				if(thisLine == previousLine)
				{
					count++;
				}
				else
				{
					if(count!=1)
					{
						//cout<<count<<"\t"<<previousLine<<endl;
						printf("%7lu ",count);
						cout<<previousLine<<endl;
						count=1;
					}
					else
					{
						count=1;
					}
				}
				previousLine = thisLine;
			} while(getline(cin, thisLine));
			if(count!=1)
			{
				//cout<<count<<"\t"<<previousLine<<endl;
				printf("%7lu ",count);
				cout<<previousLine<<endl;
			}
		}

		else if(uniqonly==1)
		{
			size_t count=1;
			string thisLine, previousLine;
			getline(cin, previousLine);
			getline(cin, thisLine);
			do
			{
				if(thisLine==previousLine)
				{
					count++;
				}
				else
				{
					if(count==1)
					{
						//cout<<count<<"\t"<<previousLine<<endl;
						printf("%7lu ",count);
						cout<<previousLine<<endl;
						count=1;
					}
					else
					{
						count=1;
					}
				}
				previousLine=thisLine;
			} while(getline(cin, thisLine));
			if(count==1)
			{
				//cout<<count<<"\t"<<previousLine<<endl;
				printf("%7lu ",count);
				cout<<previousLine<<endl;
			}
		}

		else
		{
			size_t count=1;
			string thisLine, previousLine;
			getline(cin, previousLine);
			getline(cin, thisLine);
			do
			{
				if(thisLine == previousLine)
				{
					count++;
				}
				else
				{
					//cout<<count<<"\t"<<previousLine<<endl;
					printf("%7lu ",count);
					cout<<previousLine<<endl;
					count=1;
				}
				previousLine = thisLine;
			} while(getline(cin, thisLine));
			//cout<<count<<"\t"<<previousLine<<endl;
			printf("%7lu ",count);
			cout<<previousLine<<endl;
		}
	}

	else if(dupsonly==1)
	{
		if(uniqonly==1)
		{
			return 0;
		}
		bool print=false;
		string thisLine, previousLine;
		getline(cin, previousLine);
		getline(cin, thisLine);
		do
		{
			if(thisLine==previousLine)
			{
				print=true;
			}
			else
			{
				if(print)
				{
					cout<<previousLine<<endl;
					print=false;
				}
			}
			previousLine = thisLine;
		} while(getline(cin, thisLine));
		if(print)
		{
			cout<<previousLine<<endl;
		}
	}

	else if(uniqonly==1)
	{
		size_t count=1;
		string thisLine, previousLine;
		getline(cin, previousLine);
		getline(cin, thisLine);
		do
		{
			if(thisLine==previousLine)
			{
				count++;
			}
			else
			{
				if(count==1)
				{
					cout<<previousLine<<endl;
					count=1;
				}
				else
				{
					count=1;
				}
			}
			previousLine=thisLine;
		} while(getline(cin, thisLine));
		if(count==1)
		{
			cout<<previousLine<<endl;
		}
	}

	else
	{
		string previousLine, thisLine;
		getline(cin, previousLine);
		getline(cin, thisLine);
		do
		{
			if(thisLine!=previousLine)
			{
				cout<<previousLine<<endl;
			}
			previousLine=thisLine;
		} while(getline(cin, thisLine));
		if(thisLine!=previousLine)
		{
			cout<<previousLine<<endl;
		}
	}

	return 0;
}
