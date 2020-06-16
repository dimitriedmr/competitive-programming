#include <stdio.h>

using namespace std;

template<typename T>
T binExp(T base, T exponent, T modulo)
{
    // eg: 3^11 = 3^(1011) = 3^8 * 3^2 * 3^1
    
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
  // https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3671
  
  //freopen ("myfile.in","r",stdin);
  //freopen ("myfile.out","w",stdout);
  
  unsigned long long cases = 0, x = 0, y = 0, n = 0, z = 0; 
  scanf("%llu",&cases);
  while(cases > 0)
  {  
	scanf("%llu %llu %llu",&x,&y,&n);
	
	z = binExp<unsigned long long>(x,y,n);
	
	printf ("%llu",z);
	printf ("\n");
	
	cases = cases - 1;
  }
  scanf("%llu",&x); // read dummy 0
  
  //fclose (stdout);
  //fclose (stdout);
  
  return 0;
}
