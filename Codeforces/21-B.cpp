#include <bits/stdc++.h>

int main()
{
    using namespace std;
  
    int t = 0, k = 0, n = 0, pos = 0, i = 0;
    string s("");

    cin.tie(0) -> sync_with_stdio(0);
    
    cin >> t;
    while (t --) {
        cin >> s >> k;

        n = s.length();
        pos = n - k;
        for (i = n - k - 1; i >= 0; i--) {
            if (s[i] > s[i + k]) {
                pos = i;
            }       
        }
        s.erase(pos, k);
        cout << s;

        cout << endl;
    }

    return 0;
}
