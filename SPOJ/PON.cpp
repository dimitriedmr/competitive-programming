#include <iostream>
#include <initializer_list>
using namespace std;
using u64 = uint64_t;
using u128 = __uint128_t;
using i128 = __int128_t;
    
u64 binExp(u64 base, u64 exponent, u64 modulo)
{
  u64 answer = 1;
  u64 newPower = base % modulo;
  while(exponent > 0 )
    {
    if(exponent & 1)
    {
      answer = (u128)answer * newPower % modulo; 
    }
    exponent = exponent >> 1;
    newPower = (u128)newPower * newPower % modulo;
  }
  return answer;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binExp(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    //A000040 from OEIS
    //first four are sufficient for n < 2^31-1
    //first twelve are sufficient for n < 2^63-1
    for (u64 a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,\
                 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89,\
                 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149,\
                 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,\
                 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}
int main ()
{
  // problem statement:
  // https://www.spoj.com/problems/PON/
    
  u64 t = 0, N = 0; 
  cin >> t;
  while(t > 0)
  {  
    cin >> N;
    if(MillerRabin(N))
      cout<< "YES";
    else
      cout<< "NO";
    cout<<endl;
    t = t - 1;
  }
  return 0;
}
