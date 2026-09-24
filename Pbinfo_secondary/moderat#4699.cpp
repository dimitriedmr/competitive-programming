#include <bits/stdc++.h>
using namespace std;


int prim ( int n )
{
    int d=2;
    if(n<2) return 0;
    else
    for( d=2; d*d<=n; d++)
        if( n % d == 0 )
            return 0;
    return 1;
}

int Moderat ( int n )
{
    int i;
    int ans = 0;
    int b = 0;
    for(int a = (int) ceil(sqrt(n)) ; a>=2; a--)
    {
    if( !(n % a) && prim(a) )
    {
        b = n / a;
        if(prim(b))
        {
            for(i = a + 1; i < b && !prim(i); i++);
            if(i == b) ans = 1;
        }
    }
    
    }
    return ans;
}

int main()
{
    int n;
    cin >> n;
    cout << Moderat(n);
    return 0;

}