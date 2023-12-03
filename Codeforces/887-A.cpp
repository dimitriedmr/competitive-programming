#include <bits/stdc++.h>

using namespace std;

int main()
{

  long t = 0, n = 0, a = 0, a2 = 0, diff = 0;

  cin >> t;

  while(t--)
  {
    diff = LONG_MAX;
    cin >> n >> a;
    --n;
    while(n > 0)
    {
      cin >> a2;

      a = a2 - a;
      if(a < diff)
        diff = a;
      a = a2;
      --n;
      
    }

    if(diff < 0)
      cout << 0;
    else
      cout << diff / 2 + 1;
    cout << endl;

  }

  return 0;
} 

