#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;

string LongestWord(string sen) {
  string word = "";
  bool bWordStart = false;
  unsigned long count = 0, max = 0;
  auto wordStart = sen.begin(), it = wordStart;
  for(it = sen.begin(); it != sen.end(); ++it)
  {
    if(isalpha(*it) || isdigit(*it))
    {
      
      if(!bWordStart)
      {
        bWordStart = true;
        count = 0;
        wordStart = it;
      }
      else
      {
        ++count;
      }
      
    }
    else
    {
        if(max < count)
        {
          max = count;
          word.assign(wordStart,it);
        }
        bWordStart = false;
    }
  }
  if(max < count)
  {
    max = count;
    word.assign(wordStart,it);
  }
  
  return word;

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

  cout << LongestWord(A) << endl;

  return 0;
    
}
