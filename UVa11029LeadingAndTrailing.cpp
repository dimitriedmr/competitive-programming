#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Solution
{
  private:
    T tBase, tPower;
    T keepDigits;
    void numberGetLeadAndTrail (T& LLL, T& TTT);
  public: 
    Solution ():tBase(0), tPower(0), keepDigits(3){};
    void readParameters ();
    string binExp ();
};

template <class T>
void Solution<T>::numberGetLeadAndTrail (T& LLL, T& TTT)
{
  
  T powerOf10 = 1;
  T LLLcopy = LLL;
  T LLLreverse = 0;
  //prepare power of 10 used to extract digits
  for(T noDigits = this->keepDigits; noDigits > 0; --noDigits)
  {
    powerOf10 *= 10;
  }
  //extract leading digits
  while(LLLcopy > 0)
  {
    LLLreverse = LLLreverse * 10 + LLLcopy % 10;
    LLLcopy /= 10;
  }
  LLLreverse %= powerOf10;
  LLL = 0;
  while(LLLreverse > 0)
  {
    LLL = LLL * 10 + LLLreverse % 10;
    LLLreverse /= 10;
  }
  //fix zeros
  while(LLL < (powerOf10 / 10))
  {
    LLL *= 10;
  }
  //extract trailing digits
  TTT %= powerOf10;
}

template <class T>
string Solution<T>::binExp ()
{
  string answer = "";
  T base = this -> tBase, power = this -> tPower;
  this -> keepDigits = 9; //increase accuracy 
  T LLLanswer = 1, TTTanswer = 1;
  
  T LLLfactor = base, TTTfactor = base;
  numberGetLeadAndTrail(LLLfactor,TTTfactor);
  
  while(power > 0)
  {
    cout<<base<<' '<<power;
    cout<<" LLL: "<<LLLanswer<<' '<<LLLfactor;
    cout<<" TTT: "<<TTTanswer<<' '<<TTTfactor<<endl;
    if(power & 1)
    {
      LLLanswer *= LLLfactor, TTTanswer *= TTTfactor;
      numberGetLeadAndTrail(LLLanswer,TTTanswer);
      
    }
    LLLfactor *= LLLfactor, TTTfactor *= TTTfactor;
    numberGetLeadAndTrail(LLLfactor,TTTfactor);
    
    power = power >> 1;
  }
  
    cout<<base<<' '<<power;
    cout<<" LLL: "<<LLLanswer<<' '<<LLLfactor;
    cout<<" TTT: "<<TTTanswer<<' '<<TTTfactor<<endl;
  this -> keepDigits = 3;
  numberGetLeadAndTrail(LLLanswer,TTTanswer);
  answer = to_string(LLLanswer) + "..." + to_string(TTTanswer);
  
  return answer;
}

template <class T>
void Solution<T>::readParameters ()
{
  cin >> this->tBase >> this->tPower;
}

int main ()
{
  // problem statement:
  // https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1970
  
  int testcases = 0;
  cin >> testcases;
  Solution<unsigned long long> s;
  
  while (testcases > 0)
  { 
    s.readParameters();
    cout << s.binExp() << endl;
    
    testcases--;
  }
    
  return 0;
}

