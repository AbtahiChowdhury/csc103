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

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
#include <map>
using std::map;
using std::make_pair;
#include <string.h> // for c-string functions.
#include <getopt.h> // to parse long arguments.

static const char* usage =
"Usage: %s [OPTIONS] SET1 [SET2]\n"
"Limited clone of tr.  Supported options:\n\n"
"   -c,--complement     Use the complement of SET1.\n"
"   -d,--delete         Delete characters in SET1 rather than translate.\n"
"   --help          show this message and exit.\n";

void escape(string& s)
{
	/* NOTE: the normal tr command seems to handle invalid escape
	 * sequences by simply removing the backslash (silently) and
	 * continuing with the translation as if it never appeared. */
	/* TODO: write me... */
	for(unsigned int i=0; i<s.size(); i++)
	{
		if(s[i]=='\\')
		{
			//cout<<"1: "<<s<<"\t"<<s[i]<<"\t"<<s[i+1]<<endl;
			if(s[i+1] != 'n' && s[i+1] != 't' && s[i+1] != '\\')
			{
				s.erase(s.begin()+i);
			}
			//cout<<"2 :"<<s<<endl;
		}
	}
}

int main(int argc, char *argv[])
{
	// define long options
	static int comp=0, del=0;
	static struct option long_opts[] = {
		{"complement",      no_argument,   0, 'c'},
		{"delete",          no_argument,   0, 'd'},
		{"help",            no_argument,   0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "cdh", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'c':
				comp = 1;
				break;
			case 'd':
				del = 1;
				break;
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}
	if (del) {
		if (optind != argc-1) {
			fprintf(stderr, "wrong number of arguments.\n");
			return 1;
		}
	} else if (optind != argc-2) {
		fprintf(stderr,
				"Exactly two strings must be given when translating.\n");
		return 1;
	}
	string s1 = argv[optind++];
	string s2 = (optind < argc)?argv[optind]:"";
	/* process any escape characters: */
	escape(s1);
	escape(s2);
	//cout<<s1<<"::"<<s2<<endl;

	/* TODO: finish this... */

	if(del!=1&&comp!=1)
	{
		map<char,char> M;
		vector<char> in, out;
		char temp;

		for(unsigned int i=0; i<s1.size(); i++)
		{
			if(s1[i]=='\\')
			{
				if(s1[i+1]=='\\')
				{
					temp='\\';
				}
				else if(s1[i+1]=='t')
				{
					temp='\t';
				}
				else if(s1[i+1]=='n')
				{
					temp='\n';
				}
				in.push_back(temp);
				i++;
			}
			else
			{
				in.push_back(s1[i]);
			}
		}

		for(unsigned int i=0; i<s2.size(); i++)
		{
			if(s2[i]=='\\')
			{
				if(s2[i+1]=='\\')
				{
					temp='\\';
				}
				else if(s2[i+1]=='t')
				{
					temp='\t';
				}
				else if(s2[i+1]=='n')
				{
					temp='\n';
				}
				out.push_back(temp);
				i++;
			}
			else
			{
				out.push_back(s2[i]);
			}
		}

		for(unsigned int i=0; i<in.size(); i++)
		{
			M[in[i]]=out[i];
		}

		/*
		for(map<char,char>::iterator i=M.begin(); i!=M.end(); i++)
		{
			cout<<(*i).first<<"->"<<(*i).second<<endl;
		}

		for(unsigned int i=0; i<in.size(); i++)
		{
			cout<<in[i]<<"->"<<out[i]<<endl;
		}
		*/

		string nextLine;
		while(getline(cin, nextLine))
		{
			for(unsigned int i=0; i<nextLine.size(); i++)
			{
				for(map<char,char>::iterator j=M.begin(); j!=M.end(); j++)
				{
					if(nextLine[i]==(*j).first)
					{
						nextLine[i]=(*j).second;
						//nextLine[i]=s2[(j+s2.size())%s2.size()];
					}
				}
			}
			cout<<nextLine<<endl;
		}
	}

	if(comp==1)
	{
		if(del==1)
		{
			vector<char> in;
			string nextLine, newline;
			while(getline(cin, nextLine))
			{
				for(unsigned int i=0; i<nextLine.size(); i++)
				{
					in.push_back(nextLine[i]);
				}

				for(unsigned int i=0; i<in.size(); i++)
				{
					for(unsigned int j=0; j<s1.size(); j++)
					{
						if(in[i]==s1[j])
						{
							newline+=in[i];
							//cout<<newline<<endl;
						}
					}
				}

				cout<<newline<<endl;
				newline.clear();
				in.clear();
			}
		}
		else
		{
			//fix this later
			map<char,char> M;
			vector<char> in, out;
			char temp;

			for(unsigned int i=0; i<s1.size(); i++)
			{
				if(s1[i]=='\\')
				{
					if(s1[i+1]=='\\')
					{
						temp='\\';
					}
					else if(s1[i+1]=='t')
					{
						temp='\t';
					}
					else if(s1[i+1]=='n')
					{
						temp='\n';
					}
					in.push_back(temp);
					i++;
				}
				else
				{
					in.push_back(s1[i]);
				}
			}

			for(unsigned int i=0; i<s2.size(); i++)
			{
				if(s2[i]=='\\')
				{
					if(s2[i+1]=='\\')
					{
						temp='\\';
					}
					else if(s2[i+1]=='t')
					{
						temp='\t';
					}
					else if(s2[i+1]=='n')
					{
						temp='\n';
					}
					out.push_back(temp);
					i++;
				}
				else
				{
					out.push_back(s2[i]);
				}
			}

			for(unsigned int i=0; i<in.size(); i++)
			{
				M[in[i]]=out[i];
			}

			/*
			for(map<char,char>::iterator i=M.begin(); i!=M.end(); i++)
			{
				cout<<(*i).first<<"->"<<(*i).second<<endl;
			}

			for(unsigned int i=0; i<in.size(); i++)
			{
				cout<<in[i]<<"->"<<out[i]<<endl;
			}
			*/

			string nextLine;
			while(getline(cin, nextLine))
			{
				for(unsigned int i=0; i<nextLine.size(); i++)
				{
					for(map<char,char>::iterator j=M.begin(); j!=M.end(); j++)
					{
						if(nextLine[i]!=(*j).first)
						{
							nextLine[i]=(*j).second;
						}
					}
				}
				cout<<nextLine<<endl;
			}
		}
	}

	if(del==1)
	{
		string nextLine;
		int len, i;

		while(getline(cin, nextLine))
		{
			len=nextLine.size();
			i=0;
			while(i<len)
			{
				for(unsigned int j=0; j<s1.size(); j++)
				{
					if(nextLine[i]==s1[j])
					{
						nextLine.erase(nextLine.begin()+i);
						i--;
						len--;
						//cout<<nextLine<<endl<<i<<"\t"<<len<<endl;
					}
				}
				i++;
			}
			cout<<nextLine<<endl;
		}
	}
	return 0;
}
