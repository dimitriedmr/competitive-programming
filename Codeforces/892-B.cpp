#include <bits/stdc++.h>
using namespace std;

#define LEN_N 25001

struct {

    vector<pair<long, long>> a;
    // I cand move only one element, thus there is no need to store more than 2.
    long n;

    void init(void) {
        n = 0;
        a.resize(LEN_N);
    }

    void read(void) {
        long x = 0;
        int m = 0, i = 0, j = 0;
        cin >> n;
        for (i = 0; i < n; ++i) 
        {
            cin >> m >> a[i].first >> a[i].second;
            // find first 2 minimums
            if (a[i].first > a[i].second) // swap
            {
                x = a[i].first;
                a[i].first = a[i].second;
                a[i].second = x;
            }
            for (j = 2; j < m; ++j) 
            {
                cin >> x;
                if (x < a[i].first)
                {
                    a[i].second = a[i].first;
                    a[i].first = x;
                }
                else if (x < a[i].second)
                {
                    a[i].second = x;
                }
            }
            // set first as max of them
            if (a[i].first < a[i].second) // swap
            {
                x = a[i].first;
                a[i].first = a[i].second;
                a[i].second = x;
            }
        }
    }

    void display(void) {
        int i = 0;
        for (i = 0; i < n; ++i) 
        {
            cout << a[i].first << ' ' << a[i].second << '\n';
        }
    }

    long long solve(){
        long long sum = 0;
        int i = 0;
        sort(a.begin(), a.begin() + n);
        // display();
        for (i = n - 1; i > 0; --i) 
        {
            sum += a[i].first;
            if (a[0].second > a[i].second)
                a[0].second = a[i].second;
        }
        sum += a[0].second;
        return sum;
    }

    void deinit(){
        int i = 0;
        a.clear();
    }

} p;

int main()
{
    int t = 0, n = 0, m = 0;
    p.init();
    cin.tie(0) -> sync_with_stdio(0);
    cin >> t;
    while (t--) 
    {
        p.read();
        cout << p.solve();
        cout << endl;
    }
    p.deinit();
    return 0;
}
