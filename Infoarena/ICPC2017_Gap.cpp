#include <iostream>
	
#include <fstream>
	
using namespace std;
	
 
	
unsigned long long cf[10], x,t;
	
unsigned long long primaCf, nr1, nr2, cfmax1, cfmax2, difmax;
	
 
	
ifstream in("gap.in");
	
ofstream out("gap.out");
	
 
	
unsigned long long tryWithCfMax(unsigned long long cfmax1)
	
{
	
    cfmax2 = 0;
	
    for (unsigned long long i = cfmax1-1; i>= 1; i--)
	
    {
	
        if (cf[i])
	
        {
	
            cfmax2 = i;
	
            break;
	
        }
	
    }
	
 
	
    if (cfmax2 == 0)
	
    {
	
        return 0;
	
    }
	
 
	
    nr1 = cfmax1;
	
    cf[cfmax1]--;
	
    for (unsigned long long i = 1; i <= 9; i ++)
	
    {
	
        for (unsigned long long j = 1; j <= cf[i] ; j ++)
	
        {
	
            nr1 = nr1 * 10 + i;
	
        }
	
    }
	
    cf[cfmax1]++;
	
 
	
    nr2 = cfmax2;
	
    cf[cfmax2]--;
	
    for (unsigned long long i = 9; i >= 1; i --)
	
    {
	
        for (unsigned long long j = 1; j <= cf[i] ; j ++)
	
        {
	
            nr2 = nr2 * 10 + i;
	
        }
	
    }
	
    cf[cfmax2]++;
	
    return nr1-nr2;
	
}
	
 
	
 
	
int main()
	
{
	
    in >> t;
	
    while (t--)
	
    {
	
        difmax = 0;
	
        in >> x;
	
        for (unsigned long long i = 1; i<= 9; i++)
	
            cf[i] = 0;
	
 
	
        while (x)
	
        {
	
            cf[x%10]++;
	
            x/=10;
	
        }
	
        for (unsigned long long i = 9; i>= 1; i--)
	
        {
	
            if (cf[i])
	
            {
	
                cfmax1 = i;
	
                difmax = max(difmax, tryWithCfMax(cfmax1));
	
            }
	
        }
	
        out << difmax << "\n";
	
    }
	
 
	
}
