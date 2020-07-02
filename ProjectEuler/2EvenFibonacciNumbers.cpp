#include <stdio.h>
#include <algorithm>
using namespace std;
//F0=0,F1=1,Fk=Fk−1+Fk−2
#define F0 0u
#define F1 1u
#define Fn 4000000u
template<typename T>
T solve () {
  T sum = 0, Fkm2 = 0, Fkm1 = 1, Fk = 1;
  while (Fk < Fn)
  {
    if(!(Fk & 1))
    {
      sum = sum + Fk;
    }
    Fk = Fkm1 + Fkm2;
    Fkm2 = Fkm1;
    Fkm1 = Fk;
  }
  return sum;
}

int main ()
{
  // problem statement:
  // https://projecteuler.net/problem=2
    
  unsigned long long sum = solve<unsigned long long>();
  printf ("%llu\n",sum);
  
  return 0;
}
