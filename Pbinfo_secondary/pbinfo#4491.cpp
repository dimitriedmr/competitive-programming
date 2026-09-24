#include <iostream>
#include <fstream>
using namespace std;



int sol[11], n, m;

void init(int k)
{
    sol[k] = 0;
}

int exista(int k)
{
   int r = 0;
   if(sol[k] < n)
        r = 1;
   return r;
}

int cont(int k)
{
   int r = 1;
   int i;
   for(i = 1; i <= k - 1; i++)
       if(sol[i] == sol[k])
            r = 0;
    if (k == m && sol[k] != n)
        r = 0;
    return r;
}

int solutie(int k)
{
    int r = 0;
    if(k == n && sol[m] == n)
        r = 1;
    return r;
}

void tipar(int k)
{
    int i;
    for (i = 1; i <= k; i++)
        cout << sol[i] << ' ';
    cout << endl;
}

void bkt()
{
    int k = 1;
    init(k);
    while(k > 0)
    {
        if(exista(k))
        {
            sol[k] = sol[k] + 1;
            if(cont(k))
                if(solutie(k))
                    tipar(k);
                else
                {
                    k = k + 1;
                    init(k);
                }
        }
        else k = k - 1;
    }
}

int main()
{
    cin >> n;
    m = n / 2 + 1;
    bkt();
}