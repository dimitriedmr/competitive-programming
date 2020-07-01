#include <iostream>
	
#include <cstdio>
	
#include <fstream>
	
using namespace std;
	
 
	
FILE* in = fopen("fences.in","r");
	
FILE* out = fopen("fences.out","w");
	
 
	
int main()
	
{
    //https://www.infoarena.ro/problema/fences
    unsigned int tests;
	
    char c;
	
    unsigned long lefts,rights,ups,downs;
	
    unsigned long long area;
	
    fscanf(in,"%u",&tests);
	
    getc(in);
	
    while(tests--)
	
    {
	
        lefts=0;rights=0;ups=0;downs=0;area=0;
	
        c = getc(in);
	
        while(c!='\n' && c != EOF)
	
        {
	
            switch (c)
	
            {
	
            case 'L': lefts++;break;
	
            case 'R': rights++;break;
	
            case 'U': ups++;break;
	
            case 'D': downs++;break;
	
            }
	
 
	
            c = getc(in);
	
        }
	
 
	
        if(lefts<rights)    area=lefts;
	
        else                area=rights;
	
 
	
        if(ups<downs)       area*=ups;
	
        else                area*=downs;
	
 
	
        fprintf(out,"%llu\n",area);
	
 
	
    }
	
    return 0;
	
}
