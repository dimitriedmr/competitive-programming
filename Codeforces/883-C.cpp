#include <bits/stdc++.h>

void solve()
{
    long long n = 0, i = 0, m = 0, k = 0, j = 0, sum = 0, cnt = 0, pen = 0, rP = 0, rC = 0;
    std::vector<long long> a;
    std::vector<std::pair<long long, long long>>p;

    std::cin >> n >> m >> k;
    a.resize(m);
    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < m; ++j)
            std::cin >> a[j];

        std::sort(a.begin(), a.end());
        sum = 0;
        pen = 0;
        cnt = 0;
        for(j = 0; j < m && sum <= k; ++j)
        {   
            if(sum + a[j] <= k)
            {
                pen += sum + a[j];
                sum += a[j];
                ++cnt;
            }
        }

        p.push_back(std::make_pair(cnt, pen));
        if(i == 0)
        {
            rP = pen;
            rC = cnt;
        }
    }

    cnt = 1;
    for(i = 0; i < n; ++i)
    {
        if(p[i].first > rC || (p[i].first == rC && p[i].second < rP))
            ++cnt;
        
    }
    std::cout << cnt;
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
