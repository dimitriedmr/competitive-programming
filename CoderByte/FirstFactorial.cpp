#include <iostream>
#include <string>
#include <set>
#include <iostream>
#include <string>

using namespace std;


int FirstFactorial(int num) {
  
  unsigned long long x = 1;
  while(num > 0)
  {
    x *= num;
    --num;
  }  
  return x;

}


int main(void) { 
   
  // keep this function call here
  /* Note: In C++ you first have to initialize an array and set 
     it equal to the stdin to test your code with arrays. */
  //9???1???9??1???9
  //5??aaaaaaaaaaaaaaaaaaa?5?5
  int n = 0;
  cin >> n;
  cout << FirstFactorial(n) << endl;

  return 0;
    
}
