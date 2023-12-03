#include <bits/stdc++.h> 

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size() 

typedef long long ll;

int main() {
	using namespace std;

	ll t, a, b;
	cin.tie(0)->sync_with_stdio(0); 
	cin >> t;
	
	while(t--)
	{
		cin >> a >> b;			
		if(a == 1)
		{
			if(b == 2)
				a = 3;
			else
				a = 2;
		}
		else
			a = 1;
		
		cout << a;
		cout << endl;

	}
	
	return 0;
}
