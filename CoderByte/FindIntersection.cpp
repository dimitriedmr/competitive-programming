#include <iostream>
#include <string>
#include <set>

using namespace std;

#define END_SEPARATOR ','
#define START_SEPARATOR ' '

template <class T>
set<T> getNumbers(string *str)
{
  set<T> a;
  T number = 0;
  string::iterator it = str->begin();
  const string::iterator itEnd = str->end();
  do
  {
    if(*it == END_SEPARATOR)
    {
      a.insert(number);
      number = 0;
    }
    else if(*it == START_SEPARATOR)
    {
      //do nothing
    }
    else
    {
      number = number * 10 + (int)(*it-'0');
    }
    ++it;
  }while(it != itEnd);
  a.insert(number);
  return a;
}

string FindIntersection(string strArr[], int arrLength)
{
  set<unsigned long long> A = getNumbers<unsigned long long>(&strArr[0]);
  set<unsigned long long> B = getNumbers<unsigned long long>(&strArr[1]);

  auto i = A.begin();
  auto j = B.begin();
  
  while (i != A.end() && j != B.end())
  {
    cout<<*i<<" "<<*j<<endl;
    if (*i != *j)
    {
      if(*j > *i)
      {
        i = A.erase(i);
      }
      else
      {
        ++j;
      }
    }
    else if(*i == *j)
    {
      ++i;
      ++j;
    }
  }
  
  A.erase(i, A.end());
  
  strArr[0].clear(); 
  
  if(A.empty())
  {
    strArr[0] += "false";
  }
  else
  {
    for(i = A.begin(); i!=A.end(); ++i)
    {
      if(i!=A.begin())
      {
        strArr[0] += ",";
      }
      strArr[0] += to_string(*i);
    }
  }
  
  return strArr[0];

}

int main(void) { 
   
  // keep this function call here
  /* Note: In C++ you first have to initialize an array and set 
     it equal to the stdin to test your code with arrays. */

  char input [100];
  cin.getline (input,100);
  string A[2];
  A[0] = input; 
  cin.getline (input,100);
  A[1] = input; 
  int arrLength = sizeof(input) / sizeof(*input);

  cout << FindIntersection(A, arrLength) << endl;

  return 0;
    
}
