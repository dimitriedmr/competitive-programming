#include <iostream>
#include <string>

using namespace std;

template <class T>
string DecimalToReverseBinary(T nbr)
{
  T i = 0;
  string ans = "";
  while(nbr > 0)
  {
    if(nbr & 1)
    {
      ans += '1';
    }
    else
    {
      ans += '0';
    }
    nbr >>= 1;
    ++i;
  }
  while(i % 8 != 0)
  {
      ans += '0';
      ++i;
  }
  
  return ans;
}

string BinaryReversal(string str)
{
  unsigned long long nbr = 0, power = 1;
  str = DecimalToReverseBinary<unsigned long long>(stoull(str));
  for(int i = str.length()-1; i >=0; --i, power <<= 1)
  {
    if(str[i] == '1')
    {
      nbr += power; 
    }
  }
  
  return to_string(nbr);

}

int main(void) { 
   
  // keep this function call here
  /* Note: In C++ you first have to initialize an array and set 
     it equal to the stdin to test your code with arrays. */
  //9???1???9??1???9
  //5??aaaaaaaaaaaaaaaaaaa?5?5
  char input [100];
  cin.getline (input,100);
  string A = input; 

  cout << BinaryReversal(A) << endl;

  return 0;
    
}
