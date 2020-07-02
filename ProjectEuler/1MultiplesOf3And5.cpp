#include <stdio.h>
#include <algorithm>
using namespace std;

template<typename T>
T solve () {
  T sum = 0;
  for (T i = 0; i < 1000; ++i)
  {
    if(i % 3 == 0 || i % 5 == 0)
    {
      sum += i;
    }
  }
  return sum;
}

int main ()
{
  // problem statement:
  // https://projecteuler.net/problem=1
    
  unsigned long long sum = solve<unsigned long long>();
  printf ("%llu\n",sum);
  
  return 0;
}
