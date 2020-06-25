#include <stdio.h>
#include <algorithm>
using namespace std;
//gcd(a,b) = b ? gcd (b, a % b) : a;
template<typename T>
T GCD (T a, T b) {
  T temp = 0;
  while (b) {
    temp = b;
    b = a % b;
    a = temp;        
  }
  return a;
}

//avoid modulo ( is slow )
//gcd(a,b) = 2 * gcd(a,b) if a,b even
//gcd(a,b) = gcd(a,b)     if b is odd
//gcd(a,b) = gcd(b,a-b)   if a,b odd
template<typename T>
T binGCD (T a, T b) {
  T gcd = 0;
  T aTrail0 = 0, bTrail0 = 0, temp = 0;
  //gcd(nr,0) = nr
  if (!a)
    gcd = b;
  else if (!b)
    gcd = a;
  else
  {
    while (!(a&1))
    {
      a >>= 1;
      ++aTrail0;
    }
    while (!(b&1))
    {
      b >>= 1;
      ++bTrail0;
    }
    do {
      while (!(b&1))
        b >>= 1;
      if (a > b)
      {
        temp = a;
        a = b; 
        b = temp;
      }
      b -= a;
    } while (b);
    
    gcd = a << min(aTrail0,bTrail0);
  }
  return gcd;
}
template<typename T>
T LCM (T a, T b) {
  return a / binGCD(a,b) * b;
}
int main ()
{
  // problem statement:
  // https://www.codechef.com/problems/FLOW016
    
  unsigned long long t = 0, a = 0, b = 0; 
  scanf("%llu",&t);
  while(t > 0)
  {  
    scanf("%llu %llu",&a,&b);
    printf ("%llu ",binGCD<unsigned long long>(a,b));
    printf ("%llu",LCM<unsigned long long>(a,b));
    printf ("\n");
    t = t - 1;
  }
  return 0;
}
