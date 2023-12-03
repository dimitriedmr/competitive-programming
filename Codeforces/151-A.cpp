#include <bits/stdc++.h>

void solve()
{
    std::vector<unsigned> a;
    unsigned n = 0, k = 0, x = 0, i = 0;

    std::cin >> n >> k >> x; // final number, 1 ... k without x numbers
    // at the end of function, n contains number of elements in a.
    if (x != 1) // can use 1
    {
        k = n;
        while(k--) 
            a.push_back(1);
    }
    else if (k > 1) // cannot use 1
    {
        if (n % 2 == 0) // n even
        {
            n /= 2;
            k = n;
            while(k--) 
                a.push_back(2);
        }
        else // n odd
        {
            // find first odd number to obtain an even n
            for(i = 3; i <= k; i += 2)
                if(i != x)
                {
                    a.push_back(i);
                    k = (n - i) / 2;
                    n = 1 + k;
                    while(k--)
                        a.push_back(2);
                    break;
                }
            if (i == k + 1) // cannot find first odd number
                n = 0;
        }
    }
    else
    {
        n = 0;
    }
    if(n)
    {
        std::cout << "YES" << '\n' << n << std::endl;
        for(i = 0; i < n; ++i)
            std::cout << a[i] << ' ';
    }
    else
        std::cout << "NO";
    std::cout << std::endl;
}

int main () 
{
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);
    unsigned t = 0;
    std::cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
