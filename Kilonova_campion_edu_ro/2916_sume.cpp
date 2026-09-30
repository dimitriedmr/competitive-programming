#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
struct Problem
{
    ll N;
    unordered_set<ll> divs;
    map<ll, ll> result;

    void read()
    {
        cin >> N;
    }

    void divisors(const int x)
    {
        ll d = 2;
        // trivials
        divs.insert(1);
        divs.insert(x);
        // factors
        while (d * d < x)
        {
            if (x % d == 0)
            {
                divs.insert(d);
                divs.insert(x / d);
            }
            ++d;
        }
        if (d * d == x)
            divs.insert(d);
    }

    bool odd(const ll n){
        // n is odd
        return (n % 2 == 1);
    }

    bool even(const ll n){
        // n is even and N/n must be x.5 
        // <=> N/n = q*(1/2) <=> 2N=q*n <=> n | 2N
        return ((n % 2 == 0) && (N % n != 0) && (2*N % n == 0));
    }

    void add(const unordered_set<ll> *ds, bool (Problem::*const func)(const ll))
    {
        for (ll d : *ds)
            if ((this->*func)(d))
                result[d] = N / d - (d - 1) / 2;
    }

    void run(const ll N)
    {
        // first number = SUM / n + (n - 1) / 2
        // there are two cases, when: n is odd and n is even
        divs.erase(1);
        add(&divs, &Problem::odd);
        divs.insert(1);
        for (ll d : divs)
        {
            divs.insert(d * 2);
        }
        add(&divs, &Problem::even);
    }

    void print()
    {
        cout << result.size() << '\n';
        for (pair<ll, ll> r : result)
            cout << r.first << ' ' << r.second << '\n';
    }
};

int main()
{
    FILE *in = freopen("sume.in", "r", stdin);
    FILE *out = freopen("sume.out", "w", stdout);

    Problem p;
    p.read();
    p.divisors(p.N);
    p.run(p.N);
    p.print();

    fclose(in);
    fclose(out);

    return 0;
}