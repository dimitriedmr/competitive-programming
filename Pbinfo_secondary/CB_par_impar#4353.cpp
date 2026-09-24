#include <iostream>
using namespace std;

#define LEN_X (int)(1e5 + 1)
#define LEN_Y (int)(2 * 1e5 + 1)

int caut(int *v, int st, int dr, int x)
{
    /*return: position OR -1 when not found*/
    int r = -1, m = 0;

    if(st <= dr)
    {
        m = (st + dr) / 2;

        if(v[m] == x)
        {
            r = m;
        }
        else if(v[m] > x)
        {
            r = caut(v, st, m - 1, x);
        }
        else
        {
            r = caut(v, m + 1, dr, x);
        }
    }

    return r;
}

int main()
{
    int x[LEN_X] = {0}, y = 0;
    int i = 0, e = 0, o = 0, n = 0, m = 0, even_num = 0, odd_num = 0;
    // read first half and keep even numbers
    cin >> n;
    for(i = 0; i < n; ++i)
    {
        cin >> x[i];
    }
    // solve
    cin >> m;
    for(i = 0; i < m; ++i)
    {
        cin >> y;
        if(y % 2 == 0)
        {
            if(caut(x, 0, n / 2 - 1, y) >= 0)
                ++even_num;
        }
        else
        {
            if(caut(x, n / 2, n - 1, y) >= 0)
                ++odd_num;
        }
    }
    cout << even_num << ' ' << odd_num;
}
