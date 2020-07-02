#include <iostream>
#include <string>
#include <set>
#include <iostream>
#include <string>

using namespace std;

string QuestionsMarks(string str) {
  string answer = "false";
  bool bFoundOnce = false;
  unsigned int startDigit = 0, endDigit = 0;
  unsigned long long qCount = 0;
  for (auto it = str.begin(); it != str.end(); ++it)
  {
    if(*it > '0' && *it <= '9')
    {
      endDigit = (int)(*it - '0');
      if(endDigit + startDigit == 10)
      {
        if(qCount == 3)
        {
          if(!bFoundOnce)
          {
            answer = "true";
            bFoundOnce = true;
          }
        }
        else
        {
          answer = "false";
          it = str.end() - 1;
        }
      }
      qCount = 0;
      startDigit = endDigit;
    }
    else if (*it == '?')
    {
      ++qCount;
    }
  }
   
  return answer;

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

  cout << QuestionsMarks(A) << endl;

  return 0;
    
}
