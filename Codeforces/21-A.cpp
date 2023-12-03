#include <bits/stdc++.h>

using namespace std;

int main()
{

  long t = 0, n = 0, i = 0;
  vector<long> a;

  cin >> t;

  while(t--)
  {
    cin >> n;
    a.resize(n);
    for(i = 0; i < n; ++i)
	cin >> a[i];

    sort(a.begin(), a.end());
    
    for(i = 1; i < n; i = i + 2)
      a[i] = 0 - a[i];

    for(i = 0; i < n; ++i)
        cout << a[i] << ' ';

    cout << endl;

  }

  return 0;
}
