#include <algorithm>
#include <iostream>
#include <string>

using namespace std;


string FirstReverse(string str) {
  
  reverse(str.begin(),str.end());
  return str;

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

  cout << FirstReverse(A) << endl;

  return 0;
    
}
