#include <iostream>
	
#include <fstream>
	
#include <vector>
	
 
	
using namespace std;
	
 
	
ifstream in("union.in");
	
ofstream out("union.out");
	
 
	
struct punct
	
{
	
    int x, y;
	
};
	
 
	
struct dreptunghi
	
{
	
    punct p1, p2;
	
    void afis()
	
    {
	
        out << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << "\n";
	
    }
	
};
	
 
	
int M[20][20];
	
int n, m, k;
	
 
	
int ultimaColoanaNenula(int rand, int x, int y)
	
{
	
    for (int i = x; i <= y; i++)
	
    {
	
        if (M[rand][i] == 0)
	
            return i-1;
	
    }
	
    return y;
	
}
	
 
	
void fa2(int a, int c, int b, int d)
	
{
	
    for (int i = a; i <= b; i ++ )
	
        for (int j = c; j <= d; j ++)
	
            M[i][j] = 2;
	
}
	
 
	
void proces()
	
{
	
    int dreptunghiuri = 0;
	
    punct colt_ss, colt_dj;
	
    dreptunghi d;
	
    vector<dreptunghi> v;
	
 
	
    int dreapta_max, jos_max;
	
 
	
    for (int i = 0; i < n; i++)
	
    {
	
        for (int j = 0; j < m; j++)
	
        {
	
            if (M[i][j] == 1)
	
            {
	
                dreptunghiuri++;
	
 
	
                if (dreptunghiuri > k) // prea mult
	
                {
	
                    out << -1 << "\n";
	
                    return;
	
                }
	
 
	
                colt_ss.x = i;
	
                colt_ss.y = j;
	
 
	
                for (dreapta_max = colt_ss.y;
	
                dreapta_max < (m-1) && M[i][dreapta_max+1] != 0;
	
                dreapta_max++ );
	
 
	
                for (jos_max = colt_ss.x;
	
                jos_max < (n-1) && M[jos_max+1][j] != 0;
	
                jos_max++ )
	
                {
	
                    dreapta_max = min(dreapta_max,ultimaColoanaNenula(jos_max,colt_ss.y, dreapta_max));
	
                };
	
                dreapta_max = min(dreapta_max,ultimaColoanaNenula(jos_max,colt_ss.y, dreapta_max));
	
 
	
                colt_dj.x = jos_max;
	
                colt_dj.y = dreapta_max;
	
 
	
                d.p1 = colt_ss;
	
                d.p2 = colt_dj;
	
 
	
                fa2(colt_ss.x, colt_ss.y, colt_dj.x, colt_dj.y);
	
 
	
                v.push_back(d);
	
            }
	
        }
	
    }
	
    out << v.size() << "\n";
	
    for (vector<dreptunghi>::iterator it = v.begin(); it != v.end(); it ++)
	
        (*it).afis();
	
}
	
 
	
int main()
	
{
	
    int t;
	
    char c;
	
 
	
    in >> t;
	
    while (t--)
	
    {
	
        in >> n >> m >> k;
	
        for (int i = 0; i < n; i++)
	
        {
	
            for (int j = 0; j < m; j++)
	
            {
	
                in >> c;
	
                M[i][j] = c-'0';
	
            }
	
        }
	
        proces();
	
    }
	
}
