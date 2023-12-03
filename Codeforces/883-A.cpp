#include <bits/stdc++.h>
 
void solve()
{
    unsigned n = 0, a = 0, b = 0, cnt = 0;
 
    std::cin >> n;
 
    while(n--)
    {
	std::cin >> a >> b;
        if (a > b)
            ++cnt;
    }
 
    std::cout << cnt << std::endl;
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
