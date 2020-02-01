#include <iostream>
#include <cstdio>
#include <stdlib.h> // for exit();
#include <getopt.h> // to parse long arguments.
#include <unistd.h> // sleep
#include <vector>
using namespace std;
#include <string>

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Text-based version of Conway's game of life.\n\n"
"   --seed,-s     FILE     read start state from FILE.\n"
"   --world,-w    FILE     store current world in FILE.\n"
"   --fast-fw,-f  NUM      evolve system for NUM generations and quit.\n"
"   --help,-h              show this message and exit.\n";

size_t max_gen = 0; /* if > 0, fast forward to this generation. */
string wfilename =  "/tmp/gol-world-current"; /* write state here */
FILE* fworld = 0; /* handle to file wfilename. */
string initfilename = "/tmp/gol-world-current"; /* read initial state from here. */

vector<vector<bool> > world;
vector<vector<size_t> > nbrofCell;
size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g);
void update();
int initFromFile(const string& fname);
void update();
void dumpState();
void mainLoop();

char text[3] = ".O";

int main(int argc, char *argv[])
{
	// define long options
	static struct option long_opts[] =
	{
		{"seed",    required_argument, 0, 's'},
		{"world",   required_argument, 0, 'w'},
		{"fast-fw", required_argument, 0, 'f'},
		{"help",    no_argument,       0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "hs:w:f:", long_opts, &opt_index)) != -1)
	{
		switch (c)
		{
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case 's':
				initfilename = optarg;
				break;
			case 'w':
				wfilename = optarg;
				break;
			case 'f':
				max_gen = atoi(optarg);
				break;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}
	initFromFile(initfilename);
	mainLoop();
	return 0;
}

int initFromFile(const string& fname)
{
	FILE* f = fopen(fname.c_str(),"rb"); /* note conversion to char* */
	world.push_back(vector<bool>()); /* add a new row */
	size_t rows = 0; /* current row we are filling */
	char c;
	while (fread(&c,1,1,f))
	{
	    if (c == '\n')
		{
    	    /* found newline; add a new row */
        	rows++;
        	world.push_back(vector<bool>());
    	}
		else if (c == '.')
		{
			world[rows].push_back(false); /* dead x_x */
    	}
		else
		{
			world[rows].push_back(true); /* alive 8D */
    	}
	}
	fclose(f);

	world.pop_back();

	size_t h=world.size(), g=world[1].size();
	nbrofCell.resize(h);
	for (unsigned int k=0; k<world.size(); k++)
	{
		nbrofCell[k].resize(g);
	}
	return 0;
}

size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g)
{
	size_t x=0, r, c;
	r = g.size();
	c = g[1].size();
	if (g[((i-1)+r)%r][((j-1)+c)%c])
	{
		x++;
	}
	if (g[((i-1)+r)%r][((j)+c)%c])
	{
		x++;
	}
	if (g[((i-1)+r)%r][((j+1)+c)%c])
	{
		x++;
	}
	if (g[((i)+r)%r][((j-1)+c)%c])
	{
		x++;
	}
	if (g[((i)+r)%r][((j+1)+c)%c])
	{
		x++;
	}
	if (g[((i+1)+r)%r][((j-1)+c)%c])
	{
		x++;
	}
	if (g[((i+1)+r)%r][((j)+c)%c])
	{
		x++;
	}
	if (g[((i+1)+r)%r][((j+1)+c)%c])
	{
		x++;
	}
	return x;
}

void update()
{
	for (size_t k=0; k<world.size(); k++)
	{
		for (size_t l=0; l<world[1].size(); l++)
		{
			nbrofCell[k][l] = nbrCount(k,l,world);
		}
	}

	for (size_t i=0; i<world.size(); i++)
	{
		for (size_t j=0; j<world[1].size(); j++)
		{
			size_t n = nbrofCell[i][j];
			if ((world[i][j]) && (n<2 || n>3))
			{
				world[i][j] = false;
			}
			else if((world[i][j] == false) && (n==3))
			{
				world[i][j] = true;
			}
		}
	}
}

void dumpState()
{
	if (wfilename == "-")
	{
		char c;
		for (unsigned int i=0; i<world.size(); i++)
		{
			for (unsigned int j=0; j<world[1].size(); j++)
			{
				if (world[i][j])
				{
					c = 'O';
				}
				else
				{
					c = '.';
				}
				fwrite(&c,1,1,stdout);
			}
			c='\n';
			fwrite(&c,1,1,stdout);
		}
	}
	else
	{
		FILE* f = fopen(wfilename.c_str(),"wb");
		char c;
		for (unsigned int i=0; i<world.size(); i++)
		{
			for (unsigned int j=0; j<world[1].size(); j++)
			{
				if (world[i][j])
				{
					c = '0';
				}
				else
				{
					c = '.';
				}
				fwrite(&c,1,1,f);
			}
			c='\n';
			fwrite(&c,1,1,f);
		}
		fclose(f);
	}
}

void mainLoop()
{
	size_t cur_gen = 0;

	if (max_gen == 0)
	{
		while (true)
		{
			update();
			dumpState();
			cur_gen++;
			sleep(1);
		}
	}
	else
	{
		while(cur_gen<max_gen)
		{
			update();
			cur_gen++;
		}
		dumpState();
	}
}
