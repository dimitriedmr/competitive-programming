#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Problem
{
    ll N;
    vector<ll> divs;
    set<ll> divs2N;
    vector<pair<ll, ll>> result;
    const double epsilon = 0.1;

    void read()
    {
        cin >> N;
    }

    void divisors(int x)
    {
        ll d = 2;
        // trivials
        divs.push_back(1);
        divs.push_back(x);
        // factors
        while (d * d < x)
        {
            if (x % d == 0)
            {
                divs.push_back(d);
                divs.push_back(x / d);
            }
            ++d;
        }
        if (d * d == x)
            divs.push_back(d);
    }

    void add(ll d)
    {
        ll first = N / d - (d - 1) / 2;
        result.push_back(make_pair(d, first));
    }

    void n_odd()
    {
        for (ll d : divs)
            if (d % 2 == 1 && d != 1) // skip a sum having one term
                add(d);
    }

    void n_even()
    {
        double fraction;
        // N/n must be x.5 <=> N/n = q*(1/2) <=> 2N=q*n <=> n | 2N
        divs2N.insert(divs.begin(), divs.end());
        for (ll d : divs)
        {
            divs2N.insert(d * 2);
        }
        for (ll d : divs2N)
            if (d % 2 == 0)
            {
                // and N/n must have .5; thus use double and avoid direct comparison
                fraction = (double)N / d;
                if (!(ceil(fraction) - fraction < epsilon))
                    add(d);
            }
    }

    void run(ll N)
    {
        // first number = SUM / n + (n - 1) / 2
        // thus there are two cases, when:
        n_odd();
        n_even();
    }

    void print()
    {
        cout << result.size() << '\n';
        sort(result.begin(), result.end());
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