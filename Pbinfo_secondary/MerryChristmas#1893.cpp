#include <iostream>

using namespace std;
#define MAX_9CF 1000000000 - 1
#define MIN_9CF 100000000

int main()
{
    int n = 0, i = 0, x = 0;
    int m = MAX_9CF, last_m = MAX_9CF, M = MIN_9CF, last_M = MIN_9CF;
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;

    for (i = 0; i < n; ++i)
    {
        cin >> x;
        if (x < m)
        {
            // update min
            if (m != last_m) // keep last minimum
                last_m = m;
            m = x;
        }
        if (x > M)
        {
            if (M != last_M)
                last_M = M;
            M = x;
        }
    }
    if (m - MIN_9CF > 1)
        cout << MIN_9CF;
    else if (MAX_9CF - M > 1)
        cout << MAX_9CF;
    else if (last_m - m > 1)
        cout << m + 1;
    else if (M - last_M > 1)
        cout << M - 1;
    else
        cout << 123456789;

    cout << endl;

    return 0;
}