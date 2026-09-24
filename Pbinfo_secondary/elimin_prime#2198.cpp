#include <iostream>
#include <cassert>
#include <forward_list>
#include <cstdio>
using namespace std;

typedef long long ll;

bool isPrime(int x)
{
    bool ans = false;
    if (x <= 2)
        ans = true;
    else
    {
        if (x % 2 != 0)
            ans = true;
        for (int d = 3; d * d <= x; d += 2)
            if (x % d == 0)
            {
                ans = false;
                d = x + 1;
            }
    }
    return ans;
}

int main()
{
    freopen("C:\\Users\\acasa\\Desktop\\pbinfo\\elimin_prime.in", "r", stdin);
    freopen("C:\\Users\\acasa\\Desktop\\pbinfo\\elimin_prime.out", "w", stdout);
    forward_list<ll> l;
    ll n = 0, i = 0, x = 0;
    cin >> n;
    assert(n <= 100000);
    auto itp = l.before_begin(), it = itp;
    for (i = 0; i < n; ++i)
    {
        cin >> x;
        it = l.insert_after(it, x);
    }

    while (!l.empty())
    {
        i = 1;
        itp = l.before_begin();
        it = l.begin();
        while (it != l.end())
        {
            if (isPrime(i))
            {
                cout << *it << ' ';
                it = l.erase_after(itp);
                --n;
            }
            else
                it = next(it);
            itp = prev(it);
            ++i;
        }
    }
    return 0;
}