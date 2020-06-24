#include <stdio.h>
using namespace std;
template<typename T>
T binExp(T base, T exponent, T modulo)
{
  T answer = 1;
  T newPower = base % modulo;
  while(exponent > 0 )
    {
    if(exponent & 1)
    {
      answer = answer * newPower % modulo; 
    }
    exponent = exponent >> 1;
    newPower = newPower * newPower % modulo;
  }
  return answer;
}
int main ()
{
  // problem statement:
  // https://www.spoj.com/problems/LASTDIG/
    
  unsigned long long t = 0, a = 0, b = 0; 
  scanf("%llu",&t);
  while(t > 0)
  {  
    scanf("%llu %llu",&a,&b);
    printf ("%llu",binExp<unsigned long long>(a,b,10)%10);
    printf ("\n");
    t = t - 1;
  }
  return 0;
}
