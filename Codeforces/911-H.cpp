#include <bits/stdc++.h>
using namespace std;

unsigned long long getMin(vector <unsigned long long> a, int n)
{
    int i = 0;
    unsigned long long m = ULLONG_MAX;
    for (i = 0; i < n; ++i)
    {
        if(a[i] < m && a[i] > 0)
            m = a[i];
    }
    return m;
}

int main()
{
    vector <unsigned long long> a;
    unsigned long long m = 0, M = 0, x = 0;
    int t = 0, n = 0, i = 0;
    cin.tie(0) -> sync_with_stdio(0);
    //cin >> t;
    t = 1;
    while(t--)
    {
        cin >> n;
        a.resize(n);
        M = 0;
        for (i = 0; i < n; ++i)
        {
            cin >> a[i];
            M += a[i];
        }
        m = 0;
        x = getMin(a, n);
        while(ULLONG_MAX != x)
        {
            for (i = 0; i < n; ++i)
            {
                if(a[i] >= x)
                    a[i] -= x;
            }
            m += x;
            x = getMin(a, n);
        }
        cout << m << ' ' << M;
        cout << endl;
    }
    return 0;
}
