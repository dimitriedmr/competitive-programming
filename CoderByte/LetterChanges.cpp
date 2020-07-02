#include <iostream>
#include <string>
#include <ctype.h>
#include <string.h>

using namespace std;

string LetterChanges(string str) {
  char vowels[6] = "aeiou";
  for(auto it = str.begin(); it != str.end(); ++it)
  {
    if(*it >= 'a' && *it <= 'z')
    {
      *it = *it + 1;
      if(strchr(vowels,*it)!=NULL)
      {
        *it = toupper(*it);
      } 
    }
  }  
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

  cout << LetterChanges(A) << endl;

  return 0;
    
}
