#include <iostream>
using namespace std;

int main()
{
    int n = 0, curent = -1, ok = 0, nr_siruri = -1;
    int sir[1001] = {};

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> sir[i];

    while (ok == 0)
    {
        ++nr_siruri;
        ok = 1;
        for (int i = 1; i <= n; i++)
        {
            if (sir[i] > -1 && curent <= sir[i])
            {
                curent = sir[i];
                sir[i] = -1;
                ok = 0;
            }
        }
        curent = -1;
    }
    cout << nr_siruri;
}
