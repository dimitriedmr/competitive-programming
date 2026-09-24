#include <iostream>
#include <fstream>
#include <array>

using namespace std;

int main()
{
    array<int, 201> a;
    int n = 0, k = 0, i = 0, m1 = 0, m2 = 0;
    cin >> k >> n;

    for (i = 0; i < n; ++i)
        cin >> a.at(i);

    for (i = 0; i < n; ++i)
    {
        m1 = a.at(i) - a.at(i) % k;
        m2 = m1 + k;
        if (a.at(i) - m1 <= m2 - a.at(i))
            a.at(i) = m1;
        else
            a.at(i) = m2;
    }

    for (i = n - 1; i >= 0; --i)
        cout << a[i] << ' ';
    cout << endl;

    return 0;
}